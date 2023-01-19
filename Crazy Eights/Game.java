/*
* Ponthea Ava Zahraii
* 2366637
* zahraii@chapman.edu
* CPSC 231-03
* MP3B: Crazy Eights!
*
* This assignment implements a class which is used to represent
* a Game of crazy eights between two players.
*/

import java.util.LinkedList;

public class Game{
  /* The dealer of the game */
  private Dealer m_dealer;
  /* A LinkedList consisting of all the cards that are in the starter pile */
  private LinkedList<Card> m_pile;
  /* The first player in the game */
  private Player m_player1;
  /* The second player in the game */
  private Player m_player2;
  /* The number of time player 1 wins */
  private int m_win1 = 0;
  /* The number of time player 2 wins */
  private int m_win2 = 0;
  /* The number of time points player 1 has */
  private int m_point1 = 0;
  /* The number of time points player 2 has */
  private int m_point2 = 0;
  /* The numebr of cards the losing player has in their hand */
  private int m_numCards = 0;
  /* The number of times the stock pile is empty */
  private int m_stock = 0;
  /* The number of times a crazy eight is played */
  private int m_eight = 0;

  /* The default constructor
  * Creates a dealer for the game
  * Creates and adds a card to the game's start pile
  * Creates 2 players for the game
  */
  public Game(){
    m_dealer = new Dealer();
    m_pile = new LinkedList<Card>();
    Card c = m_dealer.deals(1).get(0);
    m_pile.add(c);
    m_player1 = new Player(1, m_dealer, m_pile);
    m_player2 = new Player(2, m_dealer, m_pile);
  }

  /* The accessor for player 1's wins
  * return = the number of wins for player 1
  */
  public int getWin1(){
    return m_win1;
  }

  /* The accessor for player 2's wins
  * return = the number of wins for player 2
  */
  public int getWin2(){
    return m_win2;
  }

  /* The accessor for player 1's points
  * return = the number of points for player 1
  */
  public int getPoint1(){
    return m_point1;
  }

  /* The accessor for player 2's points
  * return = the number of points for player 2
  */
  public int getPoint2(){
    return m_point2;
  }

  /* The accessor for the number of cards held by the losing player
  * return = an integer representing the number of cards held by the losing player
  */
  public int getNumCards(){
    return m_numCards;
  }

  /* The accessor for the number of times the stock becomes empty
  * return = an integer represeting the number of times the stock becomes empty
  */
  public int getStock(){
    m_stock += m_player1.getStock();
    m_stock += m_player2.getStock();
    return m_stock;
  }

  /* The accessor for the number of crazy eights played in a game
  * return = an integer represeting the number of eights played in a game
  */
  public int getEight(){
    return m_eight;
  }

  /* Plays the a game of Crazy Eights
  * return = the winner of the game
  */
  public Player play(){
    /* Initializes a suit integer to use when a crazy eight is played */
    int suit = 0;
    while (true){
      /* Checks to see if there are any cards in the stock
      * if the stock is empty a new stock is created
      *   Excludes all cards in the hands of the players
      *   Excludes the last card placed in the pile
      * increments the number of times the stock became empty
      */
      if (m_dealer.size() == 0){
        ++m_stock;
        Dealer dnew = new Dealer();
        for (int card = 0; card < m_player1.getHandSize(); ++card){
          LinkedList<Card> hand = m_player1.getHand();
          dnew.remove(hand.get(card));
        }

        for (int card = 0; card < m_player2.getHandSize(); ++card){
          LinkedList<Card> hand = m_player2.getHand();
          dnew.remove(hand.get(card));
        }

        dnew.remove(m_pile.get(m_pile.size()-1));

        m_dealer = dnew;
      }

      /* Checks to see if player 1 has any cards in their hand
      * if player 1 has no cards in their hand:
      *   return = player 1 wins the game
      *   increments the number of wins player 1 has
      *   adds to player 1's total points
      * else:
      *   player 1 takes their turn
      *   if player 1 plays an 8:
      *     the suit of the 8 is randomly selected
      *     increments the number of eights played in the game
      */
      if (m_player1.getHandSize() == 0){
        ++m_win1;
        m_numCards = m_player2.getHandSize();
        for (int card = 0; card < m_player2.getHandSize(); ++card){
          if (m_player2.getHand().get(card).getRank() != 8 && m_player2.getHand().get(card).getRank() != Card.ACE){
            m_point1 += m_player2.getHand().get(card).getRank();
          } else if (m_player2.getHand().get(card).getRank() == Card.ACE){
            m_point1 += 1;
          } else {
            m_point1 += 50;
          }
        }
        return m_player1;
      } else {
        m_player1.takeTurn();
        if (m_pile.get(m_pile.size()-1).getRank() == 8){
          ++m_eight;
          suit = m_player1.newSuit();
          m_pile.get(m_pile.size()-1).setSuit(suit);
        }
      }

      /* Checks to see if player 2 has any cards in their hand
      * if player 2 has no cards in their hand:
      *   return = player 2 wins the game
      *   increments the number of wins player 2 has
      *   adds to player 2's total points
      * else:
      *   player 2 takes their turn
      *   if player 2 plays an 8:
      *     the suit of the 8 is randomly selected
      *     increments the number of eights played in the game
      */
      if (m_player2.getHandSize() == 0){
        ++m_win2;
        m_numCards = m_player1.getHandSize();
        for (int card = 0; card < m_player1.getHandSize(); ++card){
          if (m_player1.getHand().get(card).getRank() != 8 && m_player1.getHand().get(card).getRank() != Card.ACE){
            m_point2 += m_player1.getHand().get(card).getRank();
          } else if (m_player1.getHand().get(card).getRank() == Card.ACE){
            m_point2 += 1;
          } else {
            m_point2 += 50;
          }

        }
        return m_player2;
      } else {
        m_player2.takeTurn();
        if (m_pile.get(m_pile.size()-1).getRank() == 8){
          ++m_eight;
          suit = m_player2.newSuit();
          m_pile.get(m_pile.size()-1).setSuit(suit);
        }
      }
    }
  }
}
