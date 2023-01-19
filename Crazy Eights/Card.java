/*
* Ponthea Ava Zahraii
* 2366637
* zahraii@chapman.edu
* CPSC 231-03
* MP3B: Crazy Eights!
*
* This assignment implements a class which is used to represent
* Cards allowing you to identify the rank and suit of any given card.
*/

public class Card{
  /* The suits of the cards assigned to integers
  * Hearts = 0
  * Spades = 1
  * Clubs = 2
  * Diamonds = 3
  */
  public static final int HEARTS = 0;
  public static final int SPADES = 1;
  public static final int CLUBS = 2;
  public static final int DIAMONDS = 3;

  /* The rank of the face cards and the ace card
  * Jack = 11
  * Queen = 12
  * King = 13
  * Ace = 14
  */
  public static final int JACK = 11;
  public static final int QUEEN = 12;
  public static final int KING = 13;
  public static final int ACE = 14;

  /* The current suit of a card */
  private int m_suit;
  /* The current rank of a card */
  private int m_rank;

  /* The default constructor
  * Sets m_suit to the suit with the smallest int value
  * Sets m_rank to the lowest rank
  */
  public Card(){
    m_suit = HEARTS;
    m_rank = 2;
  }

  /* The overloaded constructor
  * parameter s = the suit of the card
  * parameter r = the rank of the card
  */
  public Card(int s, int r){
    m_suit = s;
    m_rank = r;
  }

  /* The copy constructor
  * parameter c = the card to copy
  */
  public Card(Card c){
    this.m_suit = c.m_suit;
    this.m_rank = c.m_rank;
  }

  /* The accessor for the suit
  * return = an int representing the suit of the card
  */
  public int getSuit(){
    return m_suit;
  }

  /* The accessor for the rank
  * return = an int represeting the rank of the card
  */
  public int getRank(){
    return m_rank;
  }

  /* The mutator for the suit
  * parameter s = the suit of the card
  */
  public void setSuit(int s){
    m_suit = s;
  }

  /* The mutator for the rank
  * parameter r = the rank of the card
  */
  public void setRank(int r){
    m_rank = r;
  }

  /* The toString method that provides a formatted string representation
  * of the card
  * return = a formatted string
  */
  public String toString(){
    String s = "";

    /* adds the rank of the card to the string */
    if (m_rank >= 2 && m_rank <= 10){
      s += m_rank;
    } else if (m_rank == JACK){
      s += "Jack";
    } else if (m_rank == QUEEN){
      s += "Queen";
    } else if (m_rank == KING){
      s += "King";
    } else if (m_rank == ACE){
      s += "Ace";
    }

    /* adds the suit of the card to the string */
    if (m_suit == HEARTS){
      s += " of Hearts";
    } else if (m_suit == SPADES){
      s += " of Spades";
    } else if (m_suit == CLUBS){
      s += " of Clubs";
    } else if (m_suit == DIAMONDS){
      s += " of Diamonds";
    }

    return s;
  }

  /* Compares an object to this Card for equality
  * parameter o = the object to compare
  * return = true if equal, false if otherwise
  */
  public boolean equals(Object o){
    if (this == o){
      return true;
    }

    if (!(o instanceof Card)){
      return false;
    }

    Card c = (Card) o;

    return this.m_rank == c.m_rank;

  }

}
