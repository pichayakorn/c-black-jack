/*******************************************************************************/
/**     Project: BLACK-JACK card game.                                        **/
/*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SUITS 4
#define NUM_RANKS 13
#define MAX_HANDCARDS 10

/** Function for Deck of cards **/
void ShowDeck();
void ShowCard(int card);
void Shuffle();
void SortDeck(); /* Don't required in program now */
void SwapDeckPosition(int firstPosition, int secondPosition);

/** Function for Black-Jack **/
void ResetHand();
void ShowBoard();
int CardScore(int card,int Player_DealerScore);
int SumCardScore(int count);
void Hit();
void DealerRules();
void CheckWin();

/** Global Variable **/
/** Constant **/
int Deck[NUM_SUITS * NUM_RANKS];

int HandCard[MAX_HANDCARDS]; //Copy Player-cards or Dealer-cards to use in SumCardScore-function.
int PlayerHandCard[MAX_HANDCARDS];
int DealerHandCard[MAX_HANDCARDS];

/** Variable **/
int CountCard = 0;
int CountPlayer = 0;
int CountDealer = 0;
int PlayerScore = 0;
int DealerScore = 0;

int main()
{
  srand(time(NULL));

  /***** GAME START *****/
  Shuffle();

  /*ShowDeck();*/ /* Use for Check processing and Hint. */
  printf("\n");

  ResetHand();
  ShowBoard();

  /***** Player turn (loop) *****/
  /* Player HIT(score less than 21) or STAND(Breakout from loop) */
  while(PlayerScore < 21)
  {
    int play;

    printf("\nHIT or STAND ?\n");
    printf("Enter (1) to \"HIT\",Enter (2) to \"STAND\": ");

    scanf("%d", &play);

    while(play != 1 && play != 2)/* Check player input 1 or 2, if not entered loop. */
    {
      printf("Invalid number, please try again.\n");
      printf("Enter (1) to \"HIT\",Enter (2) to \"STAND\": ");
      scanf("%d", &play);
    }

    printf("\n");

    if (play == 2)
    {
        /*system("cls"); printf("\n");*/
        break;
    }
    else
    {
        /*system("cls"); printf("\n");*/
        Hit();
    }
  }
  /***** Check Player score before check Dealer score *****/
  /* This code can use in function -> CheckPlayerWin -> VsDealer */
  /* Black-Jack: First 2 card with Ace and 10 point card score */
  if(PlayerScore == 21 && CountPlayer == 2)
  {
    printf("\t\tBLACK-JACK\n");
    printf("\n");
    DealerRules();
    printf("\n");
    CheckWin();
  }
  else if(PlayerScore <= 21)
  {
    DealerRules();
    printf("\n");
    CheckWin();
  }
  else /* (PlayerScore > 21) */
  {
    printf("\n");
    printf("YOU LOSE\n");
  }

  /*printf("\n"); system("PAUSE");*/

  return 0;
}

/*** Function for Deck of card *************************************************/
void ShowDeck()
{
  /* Show deck of cards in 4 row and 13 column */
  int row, column;

  for(row = 0; row < NUM_SUITS; row++)
  {
    for(column = 0; column < NUM_RANKS; column++)
    {
      ShowCard( Deck[row * NUM_RANKS + column] );
      printf("\t");
    }
    printf("\n");
  }
}

void ShowCard(int cardcode)
{
  /** Card code: 0-51.
    The suits are the order: Hearts(0-12), Diamonds(13-25), Clubs(26-38) and Spades(39-51).
    The cards are in the order: Ace, 2, 3, ...,Jack, Queen, King.
  **/
  if((cardcode % NUM_RANKS) == 0)
    printf("  A"); /*A-Ace*/
  else if ((cardcode % NUM_RANKS) < 10)
    printf("%3d", cardcode % NUM_RANKS + 1);
  else
    switch(cardcode % NUM_RANKS)
    {
      case 10:
        printf("  J"); /*J-Jack*/
        break;
      case 11:
        printf("  Q"); /*Q-Queen*/
        break;
      case 12:
        printf("  K"); /*K-King*/
        break;
    }

  switch(cardcode / NUM_RANKS)
  {
    case 0:
      printf("-H"); /*H-Hearts*/
      break;
    case 1:
      printf("-D"); /*D-Diamonds*/
      break;
    case 2:
      printf("-C"); /*C-Clubs*/
      break;
    case 3:
      printf("-S"); /*S-Spades*/
      break;
  }
}

void Shuffle()
{
  /* Set Deck of cards in order first, and shuffle cards with SwapDeckPosition-function. */
  /** Now all elements in Deck-array are storage 0 **/
  /** Assign 0-51(Card code) in ordered to Deck-array **/
  int cardcode, ranSwapDeckPosition;

  for(cardcode = 0; cardcode < (NUM_SUITS * NUM_RANKS); cardcode++)
  {
    Deck[cardcode] = cardcode;
  }

  /** Random deck position **/
  for(cardcode = (NUM_SUITS * NUM_RANKS)-1; cardcode > 1; cardcode--)
  {
    ranSwapDeckPosition = rand() % cardcode;
    SwapDeckPosition(cardcode, ranSwapDeckPosition);
  }
}
/*
void SortDeck()
{
  int firstCard, card;

  for(firstCard = 0; firstCard < (NUM_RANKS * NUM_SUITS - 1); firstCard++)
  {
    for(card = firstCard+1; card < (NUM_RANKS * NUM_SUITS); card++)
    {
      if( Deck[card] < Deck[firstCard] )
      {
        SwapDeckPosition(card, firstCard);
      }
    }
  }
}
*/
void SwapDeckPosition(int firstPosition, int secondPosition)
{
  int temp = Deck[firstPosition];
  Deck[firstPosition] = Deck[secondPosition];
  Deck[secondPosition] = temp;
}

/*** Function for Black-Jack game **********************************************/
void ResetHand()
{
  /* Reset hand to 0 card(nothing) and give player and dealer 2 cards in ordered(player first). */
  int i;
  CountPlayer = 0;
  CountDealer = 0;

  for(i = 0; i < 2; i++)
  {
    PlayerHandCard[i] = Deck[CountCard++];
    CountPlayer++;
    DealerHandCard[i] = Deck[CountCard++];
    CountDealer++;
  }
}

void Hit()
{
  PlayerHandCard[CountPlayer++] = Deck[CountCard++];
  ShowBoard();
}

void ShowBoard()
{
  /*
    Show player and dealer cards but show dealer first cards only.
    Use ShowBoard-function until call DealerRules-function.
  */
  int i;

  printf("Dealer Card : ");
  ShowCard(DealerHandCard[0]);

  printf("\nDealer Score: %3d", CardScore((DealerHandCard[0]), 0));

  printf("\n\nPlayer Card : ");
  for(i = 0; i < CountPlayer; i++)
    ShowCard(PlayerHandCard[i]);

  for(i = 0; i < MAX_HANDCARDS; i++)
  {
    HandCard[i] = PlayerHandCard[i];
  }

  PlayerScore = SumCardScore(CountPlayer);
  printf("\nPlayer Score: %3d", PlayerScore);

  printf("\n");
}

int SumCardScore(int count)
{
  int i, sum;
  sum = 0;

  for(i = 0; i < count; i++)
  {
    sum += CardScore(HandCard[i], sum);
  }

  return sum;
}

int CardScore(int card, int Player_DealerScore)
{
  if((card % NUM_RANKS) == 0)
  {
    if(Player_DealerScore >= 11)
      return 1;
    else
      return 11;
  }
  else if ((card % NUM_RANKS) < 10)
    return card % NUM_RANKS + 1;
  else
    return 10;
}

void DealerRules()
{
  int i;

  for(i = 0; i < MAX_HANDCARDS; i++)
    HandCard[i] = DealerHandCard[i];
  DealerScore = SumCardScore(CountDealer);

  while(DealerScore < 17) /* Dealer must HIT until score over 16 point. */
  {
    DealerHandCard[CountDealer++] = Deck[CountCard++];
    for(i = 0; i < MAX_HANDCARDS; i++)
      HandCard[i] = DealerHandCard[i];
    DealerScore = SumCardScore(CountDealer);
  }

  /* Same as ShowBoard-function but show all dealer-cards */
  printf("Dealer Card : ");
  for(i = 0; i < CountDealer; i++)
    ShowCard(DealerHandCard[i]);

  printf("\nDealer Score: %3d", DealerScore);

  printf("\n\nPlayer Card : ");
  for(i = 0; i < CountPlayer; i++)
    ShowCard(PlayerHandCard[i]);

  for(i = 0; i < MAX_HANDCARDS; i++)
    HandCard[i] = PlayerHandCard[i];

  printf("\nPlayer Score: %3d", PlayerScore);

  printf("\n");
}

void CheckWin()
{
  if(DealerScore > 21)
    printf("YOU WIN\n");
  else if(DealerScore > PlayerScore)
    printf("YOU LOSE\n");
  else if(DealerScore == PlayerScore)
    printf("DRAW\n");
  else
    printf("YOU WIN\n");
}
