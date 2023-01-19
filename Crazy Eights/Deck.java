/*
* Ponthea Ava Zahraii
* 2366637
* zahraii@chapman.edu
* CPSC 231-03
* MP3B: Crazy Eights!
*
* This assignment implements a class which is used to represent
* Deck allowing you to create a deck of 52 cards and deal a random
* card from this deck.
*/

import java.util.Random;
import java.util.LinkedList;

public class Deck{
  /* A LinkedList made of cards */
  private LinkedList<Card> m_cards;

  /* The default constructor
  * contains all 52 cards
  */
  public Deck(){
    m_cards = new LinkedList<Card>();
    for (int suit = Card.HEARTS; suit <= Card.DIAMONDS; ++suit){
      for (int rank = 2; rank <= Card.ACE; ++rank){
        m_cards.add(new Card(suit, rank));
      }
    }
  }

  /* The copy constructor
  * parameter d = the deck to copy
  */
  public Deck(Deck d){
    this.m_cards = new LinkedList<Card>(d.m_cards);
  }

  /* The remove method
  * removes a card from the deck
  */
  public void remove(Card c){
    m_cards.remove(c);
  }

  /* The toString method that provides a formatted string representation
  * of every card in the deck
  * return = a formatted string
  */
  public String toString(){
    String s = "";

    /* iterates through every card and prints out each card */
    for (int i = 0; i < m_cards.size(); ++i){
      s += m_cards.get(i).toString() + "\n";
    }
    return s;
  }

  /* A method looking at the size of the deck
  * return = the size of the deck
  */
  public int size(){
    return m_cards.size();
  }

  /* A method to deal a card from the deck
  * return = a card from the deck
  * Gets a random card from the deck
  * removes that card from m_cards
  */
  public Card deal(){
    Random r = new Random();
    int i = r.nextInt(m_cards.size());
    Card deal = m_cards.get(i);
    m_cards.remove(i);
    return deal;
  }
}
