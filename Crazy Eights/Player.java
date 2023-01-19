/*
* Ponthea Ava Zahraii
* 2366637
* zahraii@chapman.edu
* CPSC 231-03
* MP3B: Crazy Eights!
*
* This assignment implements a class which is used to represent
* a Player in a game of crazy eights.
*/

import java.util.LinkedList;
import java.util.Random;

public class Player{
  /* The player's number */
  private int m_player_num;
  /* The player's hand */
  private LinkedList<Card> m_hand;
  /* The dealer of the game */
  private Dealer m_dealer;
  /* A LinkedList consisting of all the cards that are in the starter pile */
  private LinkedList<Card> m_pile;
  /* A boolean flag checking if there are any crazy eights in the player's hand */
  private boolean m_eight = false;
  /* The random number generator */
  private Random r = new Random();
  /* The number of times the stock pile is empty */
  private int m_stock = 0;

  /* The overloaded constructor
  * parameter pn = player number
  * parameter d = the dealer
  * parameter p = the starter pile
  * deals 5 cards into the player's hand
  */
  public Player(int pn, Dealer d, LinkedList<Card> p){
    m_player_num = pn;
    m_dealer = d;
    m_pile = p;
    m_hand = d.deals(5);
  }

  /* The accessor for the hand size
  * return = the size of the hand
  */
  public int getHandSize(){
    return m_hand.size();
  }

  /* The accessor for the number of times the stock becomes empty
  * return = an integer represeting the number of times the stock becomes empty
  */
  public int getStock(){
    return m_stock;
  }

  /* The accessor fot the hand
  * return = a LinkedList of the cards in the hand
  */
  public LinkedList<Card> getHand(){
    return m_hand;
  }

  /* Randomly selects a suit
  * 25% chance of selecting any suit
  * return = a new suit
  */
  public int newSuit(){
    int suit = r.nextInt(4);
    return suit;
  }

  /* Takes a turn in the game */
  public Card takeTurn(){
    /* Selects a number from 0-9 to select a 10% chance */
    int random = r.nextInt(10);
    /* Used to locate the position of the 8 in the deck */
    int position = 0;
    /* sets a rank */
    int rank = 0;
    /* sets a suit */
    int suit = 0;

    /* The card to play */
    Card play = new Card();
    /* The current card in the hand */
    Card current;
    /* The card at the top of the pile */
    Card pile = m_pile.get(m_pile.size()-1);

    /* check for crazy eights in the pile */
    for (int card = 0; card < m_hand.size(); ++card){
      current = m_hand.get(card);
      if (current.getRank() == 8){
        position = card;
        m_eight = true;
        suit = current.getSuit();
        play.setSuit(suit);
        play.setRank(8);
      }
    }

    /* 10% chance of putting down a crazy 8 */
    if (m_eight){
      if (random == 8){
        m_hand.remove(position);
        m_pile.add(play);
        return play;
      }
    }

    /* if there is no crazy eight in the pile */
    for (int card = 0; card < m_hand.size(); ++card){
      current = m_hand.get(card);
      if (current.getRank() == pile.getRank() || current.getSuit() == pile.getSuit()){
        rank = current.getRank();
        suit = current.getSuit();

        play.setRank(rank);
        play.setSuit(suit);

        m_hand.remove(card);
        m_pile.add(play);
        return play;
      }
    }

    /* if there are no cards in hand that match
    * if the dealer is empty:
    *   turn is skipped
    * else:
    *   deals a card from the dealer
    *   if the dealt card matches the suit or rank of the pile card:
    *     the card is played by the player
    *   else:
    *     another card is dealt from the pile
    */
    while (true){
      if (m_dealer.size() == 0){
        return null;
      } else {
        LinkedList<Card> deals = m_dealer.deals(1);
        Card deal = deals.get(0);
        /* if the card matches the pile card */
        if (deal.getRank() == pile.getRank() || deal.getSuit() == pile.getSuit()){
          rank = deal.getRank();
          suit = deal.getSuit();

          m_dealer.remove(deal);
          play.setRank(rank);
          play.setSuit(suit);

          return play;
        } else {
          rank = deal.getRank();
          suit = deal.getSuit();
          play.setRank(rank);
          play.setSuit(suit);

          m_dealer.remove(deal);
          m_hand.add(deal);

          return deal;
        }
      }
    }
  }
}
