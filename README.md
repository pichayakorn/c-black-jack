# Blackjack

C Project: Blackjack

## The Objective of Blackjack

**Beat The Dealer**. There are some misconceptions about the objective of the game of blackjack but at the simplest level all you are trying to do is beat the dealer.

### How do you beat the dealer?

1. By drawing a hand value that is higher than the dealer’s hand value
2. By the dealer drawing a hand value that goes over 21.
3. By drawing a hand value of 21 on your first two cards, when the dealer does not.

### How do you lose to the dealer?

1. Your hand value exceeds 21.
2. The dealers hand has a greater value than yours at the end of the round

## Player decides how to play hand

`Hit` – If you would like more cards to improve your hand total, the dealer will deal you more cards, one at a time, until you either “bust” (go over 21) or you choose to stand.

`Stand` – If your first two cards are acceptable, you can stand and the dealer will move on to the next player.

## Sample (Player Vs Dealer Bot)

**Game start**

```
Dealer Card :   5-S
Dealer Score:   5

Player Card :   J-H  3-C
Player Score:  13

HIT or STAND ?
Enter (1) to "HIT",Enter (2) to "STAND":
```

**Game end: draw with dealer**

```
Dealer Card :   5-S  3-S  9-H
Dealer Score:  17

Player Card :   J-H  3-C  4-S
Player Score:  17

DRAW
```

**Game end: player lose**

```
Dealer Card :   6-D
Dealer Score:   6

Player Card :   8-C  8-D  K-H
Player Score:  26

YOU LOSE
```

**Blackjack**

```
BLACK-JACK

Dealer Card :   9-S 10-D
Dealer Score:  19

Player Card :   A-C  J-H
Player Score:  21

YOU WIN
```

## License

MIT license

Check out [LICENSE](/LICENSE) for more detail.
