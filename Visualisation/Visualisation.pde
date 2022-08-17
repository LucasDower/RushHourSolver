class Step {
  public int pieceId;
  public boolean moveForward;
  
  public Step(int pieceId, boolean moveForward) {
    this.pieceId = pieceId;
    this.moveForward = moveForward;
  }
  
  public Step(String line) {
    String[] parts = line.split(" ");
    this.pieceId = parseInt(parts[0]); // Assumes there are no more than 10 pieces
    this.moveForward = parts[1].equals("1") ? true : false;
  }
}

float lerpAlpha = 0.0;

class Piece {
  public final int len;
  public final boolean isHorizontal;
  public final color colour;
  public PVector position;
  
  public Piece(int inLength, boolean isHorizontal, color inColour, PVector inPosition) {
    this.len = inLength;
    this.isHorizontal = isHorizontal;
    this.colour = inColour;
    this.position = inPosition;
  }
}

class Board {
  private ArrayList<Piece> pieces;
  private PVector goal;

  private PVector startPos;
  private PVector endPos;
  private int pieceMoving;
  
  public Board(PVector goal) {
    this.pieces = new ArrayList<Piece>();
    this.goal = goal;
    this.pieceMoving = -1;
  }
  
  public void AddPiece(Piece piece) {
    this.pieces.add(piece);    
  }
  
  public void MovePiece(Step step) {
    Piece piece = pieces.get(step.pieceId);
    this.startPos = piece.position.copy();
    if (piece.isHorizontal) {
      piece.position.x += step.moveForward ? 1 : -1;
    } else {
      piece.position.y += step.moveForward ? 1 : -1;
    }
    this.endPos = piece.position.copy();
    this.pieceMoving = step.pieceId;
  }

  private float ease(float x) {
    x = constrain(x, 0.0, 1.0);
    return x < 0.5 ? (2 * x * x) : (1 - 2 * pow(x - 1, 2));
  }
  
  public void Draw() {
    int boardCols = 6;
    int boardRows = 6;
    
    float cellWidth = (float)width / boardCols;
    float cellHeight = (float)height / boardRows;

    for (int pieceId = 0; pieceId < this.pieces.size(); ++pieceId) {
      Piece piece = this.pieces.get(pieceId);

      fill(piece.colour);
      stroke(hue(piece.colour), saturation(piece.colour), 0.75 * brightness(piece.colour));
      
      if (pieceId != pieceMoving) {
        rect(cellWidth * piece.position.x, cellHeight * piece.position.y, cellWidth * (piece.isHorizontal ? piece.len : 1), cellHeight * (piece.isHorizontal ? 1 : piece.len));
      } else {
        PVector worldStart = new PVector(this.startPos.x * cellWidth, this.startPos.y * cellHeight);
        PVector worldEnd   = new PVector(this.endPos.x * cellWidth, this.endPos.y * cellHeight);

        float easedAlpha = this.ease(lerpAlpha);
        PVector lerped = PVector.lerp(worldStart, worldEnd, easedAlpha);

        rect(lerped.x, lerped.y, cellWidth * (piece.isHorizontal ? piece.len : 1), cellHeight * (piece.isHorizontal ? 1 : piece.len));
      }
    }

    // Draw goal
    fill(0, 0, 255);
    stroke(0, 0, 0);
    circle((this.goal.x + 0.5) * cellWidth, (this.goal.y + 0.5) * cellHeight, min(cellWidth, cellHeight) * 0.1);
  }
}

ArrayList<Step> steps;
int nextStep;
Board board;

color randomColor() {
  float k = 32;
  return color(random(k, 255 - k), 64, 255);
}

void setup() {
  size(1000, 1000);
  colorMode(HSB);
  
  steps = new ArrayList<Step>();
  for (String line : loadStrings("moves.txt")) {
    steps.add(new Step(line));
  }
  
  nextStep = -1;
  
  board = new Board(new PVector(5, 2));
  board.AddPiece(new Piece(2, true, randomColor(), new PVector(1, 0)));
  board.AddPiece(new Piece(2, true, color(0, 255, 255), new PVector(3, 2)));
  board.AddPiece(new Piece(3, true, randomColor(), new PVector(0, 3)));
  board.AddPiece(new Piece(2, true, randomColor(), new PVector(4, 4)));
  board.AddPiece(new Piece(2, true, randomColor(), new PVector(0, 5)));
  board.AddPiece(new Piece(2, true, randomColor(), new PVector(3, 5)));
  
  board.AddPiece(new Piece(3, false, randomColor(), new PVector(0, 0)));
  board.AddPiece(new Piece(2, false, randomColor(), new PVector(4, 0)));
  board.AddPiece(new Piece(2, false, randomColor(), new PVector(1, 1)));
  board.AddPiece(new Piece(2, false, randomColor(), new PVector(2, 1)));
  board.AddPiece(new Piece(2, false, randomColor(), new PVector(3, 3)));
  board.AddPiece(new Piece(2, false, randomColor(), new PVector(2, 4)));
  board.AddPiece(new Piece(3, false, randomColor(), new PVector(5, 1)));
}

void draw() {
  background(0, 0, 255);

  board.Draw(); 
  //saveFrame("frames/####.png");
  
  if (lerpAlpha >= 1.0) {
    lerpAlpha = 0.0;
    ++nextStep;

    if (nextStep < steps.size()) {
      board.MovePiece(steps.get(nextStep));
    }
  }

  lerpAlpha += 0.05;
  
  if (nextStep == steps.size() + 1) {
    exit();
  }
}
