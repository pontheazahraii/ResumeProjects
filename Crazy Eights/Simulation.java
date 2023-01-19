/*
* Ponthea Ava Zahraii
* 2366637
* zahraii@chapman.edu
* CPSC 231-03
* MP3B: Crazy Eights!
*
* This assignment implements a class which is used to represent
* a Simulation that plays a user defined number of games of crazy eights.
*/

public class Simulation{
  /* The game being played */
  private Game g;
  /* The number of time player 1 wins */
  private int m_win1;
  /* The number of time player 2 wins */
  private int m_win2;
  /* The number of time points player 1 has */
  private int m_point1;
  /* The number of time points player 2 has */
  private int m_point2;
  /* The numebr of cards the losing player has in their hand */
  private int m_numCards;
  /* The number of times the stock pile is empty */
  private int m_stock;
  /* The number of times a crazy eight is played */
  private int m_eight;


  /* The overloaded constructor
  * parameter = the number of times the game is played
  * records the statistics of the game
  */
  public Simulation(int x){
    for (int i = 0; i < x; ++i){
      g = new Game();
      g.play();
      m_win1 += g.getWin1();
      m_win2 += g.getWin2();
      m_point1 += g.getPoint1();
      m_point2 += g.getPoint2();
      m_numCards += g.getNumCards();
      m_stock += g.getStock();
      m_eight += g.getEight();
    }
    m_numCards = m_numCards / x;
    m_eight = m_eight / x;
  }

  /* The report method that provides a formatted string representation
  * of the game statistics
  * return = a formatted string
  */
  public String report(){
    String s = "";
    s += "Player 1 Stats:";
    s += "\n\tWins: " + m_win1;
    s += "\n\tPoints: " + m_point1;
    s += "\nPlayer 2 Stats:";
    s += "\n\tWins: " + m_win2;
    s += "\n\tPoints: " + m_point2;
    s += "\nGame Stats:";
    s += "\n\tAverage number of cards held by losing player: " + m_numCards;
    s += "\n\tNumber of times the stock became empty during the game: " + m_stock;
    s += "\n\tAverage number of times and eight was played: " + m_eight;
    return s;
  }

  /* The main method
  * gets input from the command line and converts it to an integer
  * plays the game the user defined number of times
  * prints out a report of all the games
  */
  public static void main(String[] args){
    int i = Integer.parseInt(args[0]);
    Simulation s = new Simulation(i);
    System.out.println(s.report());
  }
}
