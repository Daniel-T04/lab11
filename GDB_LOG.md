# GDB log

One dated section per week. Paste the commands you used and the output you saw, then explain what it means in your own words. Pasted output with no explanation earns partial credit at most. Each partner writes their own section.

## Week 11 (Lab 11)

Partner name: Daniel 

### Predict before you run


Before running `hand_bug`, which hands from the Aces Table do you expect it to get wrong, and why?

At first, I was excepting hand_bug to fail on hands with multiple Aces like AC, AD, AH and etc, because flawed implementations fail to properly the count when reducing Ace from 11 to 1.

### Build and run

```
cmake -S . -B build_bug
cmake --build build --target hand_bug
./build/hand_bug
```

Hands whose total differs from your Aces Table (hand number, printed total, correct total):

Hand 2 (AD, AC) printed total 22. the correct total is 12 since the two aces shouldn't both count as 11 and bust the hand on step 2. You can also list any 3-card multi ace hand that mismatched your table.

### The GDB session on `Hand::value`

Record the commands in the order you typed them. For each, one line on what it did.

- Conditional breakpoint command (stop only when the hand has three cards):

break Hand::value if m_count == 3

- `display` commands you set:

 display total.


- Values shown at the failing step (the running total and the number of aces counted as 11 after each `next`):

the value of total right it returned 21 or other incorrect number.

- What `print *this` showed:

 {m_cards = {{m_rank = 1, m_suit = Suit::clubs},

- What `finish` returned for the failing hand, and the correct value:

It returned 21.

### Cause and fix

- The line that is wrong, and what it does instead of what it should:

Lines 36-39, when checking total > 21  at the begging of the loop iteration before adding the card's
value, and it completely misses checking or reducing aces after the loop finishes if the final card causes a bust. Also it uses one if instead of a loop, which tells me it cannot handle multiple aces properly.

- The change you made:

Removed the if check from the beginning of the loop and added a post summation to while (total > 21 && aces_as_eleven > 0) loop at the end of the function  and correct the subtracts 10 form the total and decrements aces_as_eleven for each extra until the total is 21 or lower.

- How you checked it (which hands, which result):

I re-compiled and re-ran usinf ./build/hand_bug for all ten hands. TO verified that multi-ace hands like Hand 2(AC, AD) value 12, Hand 3 (AC, AD, 9H) value 21, and Hand 5 (AC, AD, AH) value 13,
 now it matches the expected aces Table totals instead of busting improperly.
