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
void ResetDeck();
void ShowDeck();
void ShowCard(int card);
void Shuffle();
void SwapPosition(int Array[], int firstPosition, int secondPosition);

/** Function for Black-Jack **/
void ResetHand();
void ShowBoard();
int CardScore(int card,int Player_DealerScore);
int SumCardScore(int HandCard[],int count);
void Hit();
void DealerRules();
void CheckWin();
void CheckWinWithDealer();

/** Global Variable **/
/** Constant **/
int Deck[NUM_SUITS * NUM_RANKS];

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

  /** GAME START **/
  ResetDeck();
  Shuffle();
  printf("\n");

  ResetHand();
  ShowBoard();

  /** Player turn (loop) **/
  while(PlayerScore < 21) /* Player HIT(score less than 21) or STAND(Breakout from loop) */
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
      system("cls"); printf("\n");
      break;
    }
    else
    {
      system("cls"); printf("\n");
      Hit();
    }
  }
  /** Dealer Turn (Computer) **/
  CheckWin();

  printf("\n"); system("PAUSE");

  return 0;
}

/*** Function for Deck of card *************************************************/
void ResetDeck()
{
  /** Now all elements in Deck-array are storage 0 **/
  /** Assign 0-51(Card code) in ordered to Deck-array **/
  int cardcode;

  for(cardcode = 0; cardcode < (NUM_SUITS * NUM_RANKS); cardcode++)
  {
    Deck[cardcode] = cardcode;
  }
}

void ShowDeck()
{
  /* Show deck of cards in 4 row and 13 column */
  /* Use for check under processing */
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
    The cards are in the order: Ace, 2, 3, ...,Jack, Queen, King. **/
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
  /** Random deck position **/
  int firstPosition, secondPosition;

  for(firstPosition = (NUM_SUITS * NUM_RANKS)-1; firstPosition > 1; firstPosition--)
  {
    secondPosition = rand() % firstPosition;
    SwapPosition(Deck, firstPosition, secondPosition);
  }
}

void SwapPosition(int Array[], int firstPosition, int secondPosition)
{
  int temp = Array[firstPosition];
  Array[firstPosition] = Array[secondPosition];
  Array[secondPosition] = temp;
}

/*** Function for Black-Jack game **********************************************/
void ResetHand()
{
  /** Reset hand to 0 card(nothing),
    then give player and dealer 2 cards in ordered(player first). **/
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
  /** Show player and dealer cards but show dealer first cards only. **/
  /** Use ShowBoard-function until call DealerRules-function. **/
  int i;

  printf("Dealer Card : "); ShowCard(DealerHandCard[0]);

  printf("\nDealer Score: %3d", CardScore((DealerHandCard[0]), 0));

  printf("\n\nPlayer Card : ");
  for(i = 0; i < CountPlayer; i++)
    ShowCard(PlayerHandCard[i]);

  PlayerScore = SumCardScore(PlayerHandCard, CountPlayer);
  printf("\nPlayer Score: %3d", PlayerScore);

  printf("\n");
}

int SumCardScore(int HandCard[], int count)
{
  int SortedHandCard[MAX_HANDCARDS];
  int i, j;
  int sum = 0;

  /** Assign "card score" to SortedHandCard-Array **/
  for(i = 0; i < count; i++)
    SortedHandCard[i] = HandCard[i] % NUM_RANKS;

  /** Sort "card score" from maximum to minimum. **/ /** Fix Bug A score **/
  for(i = 0; i < count-1; i++)
    for(j = i+1; j < count; j++)
      if( SortedHandCard[i] < SortedHandCard[j] )
        SwapPosition(SortedHandCard, i, j);

  for(i = 0; i < count; i++)
  {
    sum += CardScore(SortedHandCard[i], sum);
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
  DealerScore = SumCardScore(DealerHandCard, CountDealer);

  while(DealerScore < 17) /* Dealer must HIT until score over 16 point. */
  {
    DealerHandCard[CountDealer++] = Deck[CountCard++];
    DealerScore = SumCardScore(DealerHandCard, CountDealer);
  }

  /* Same as ShowBoard-function but show all dealer-cards */
  printf("Dealer Card : ");
  for(i = 0; i < CountDealer; i++)
    ShowCard(DealerHandCard[i]);

  printf("\nDealer Score: %3d", DealerScore);

  printf("\n\nPlayer Card : ");
  for(i = 0; i < CountPlayer; i++)
    ShowCard(PlayerHandCard[i]);

  printf("\nPlayer Score: %3d", PlayerScore);

  printf("\n");
}

void CheckWin()
{
  /***** Check Player score before check Dealer score *****/
  /** Black-Jack: First 2 card with Ace and 10 point card score **/
  if(PlayerScore == 21 && CountPlayer == 2)
  {
    system("cls"); printf("\n");
    printf("BLACK-JACK\n");
    printf("\n");

    DealerRules();
    printf("\n");

    CheckWinWithDealer();
  }
  else if(PlayerScore <= 21)
  {
    system("cls"); printf("\n");
    DealerRules();
    printf("\n");

    CheckWinWithDealer();
  }
  else /* (PlayerScore > 21) */
  {
    printf("\n");
    printf("YOU LOSE\n");
  }
}

void CheckWinWithDealer()
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
