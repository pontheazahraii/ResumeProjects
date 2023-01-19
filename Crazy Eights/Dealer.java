/*
* Ponthea Ava Zahraii
* 2366637
* zahraii@chapman.edu
* CPSC 231-03
* MP3B: Crazy Eights!
*
* This assignment implements a class which is used to represent
* card Dealer allowing you to deal out a certain number of cards
* from a deck.
*/

import java.util.LinkedList;

public class Dealer{
  /* A deck of cards */
  private Deck m_deck;

  /* the default constructor
  * creates a new deck of cards
  */
  public Dealer(){
    m_deck = new Deck();
  }

  /* The remove method
  * removes a card from the deck
  */
  public void remove(Card c){
    m_deck.remove(c);
  }

  /* A method that deals an n number of card from the deck and adds it
  * to a seperate LinkedList of cards
  * return = an empty LinkedList if the deck is empty
  * return = a LinkedList that consists of n cards delt randomly from the deck
  */
  public LinkedList<Card> deals(int n){
    LinkedList <Card> ll = new LinkedList<Card>();
    if (n == 0){
      return null;
    } else {
      for (int i = 0; i < n; ++i){
        ll.add(m_deck.deal());
      }
      return ll;
    }
  }

  /* A method looking at the size of the deck
  * return = the size of the deck
  */
  public int size(){
    return m_deck.size();
  }

  /* The toString method that provides a formatted string representation
  * of every card in the deck does not include the cards that were put
  * into the LinkedList of cards in the deals method
  * return = a formatted string
  */
  public String toString(){
    String s = "";
    s += m_deck.toString();
    return s;
  }

}
