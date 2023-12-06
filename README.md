# TicketMistress
TicketMistress is simple statistical program, designed to calculate the probability of a specific make, model, color, year, and state registration of car compared to other cars with one or more independent variables.
It uses two comparable data structures to accomplish this, a hash map, and a multi-typed set structure without a ADT equivalent.
Both use a supporting Ticket data structure to store individual tickets and pass around query information.

### Ticket
Ticket is simply a struct containing five enum values for state registration, make, model, color, and year.
It has a two constructors, and no other methods associated with it, because it is the ideal of data encapsulation.

### BongoTree
BongoTree contains five maps for each of the five attributes, and each map contains pairs of enum values and sets of Ticket pointers with a characteristic matching the enum values.
The three important methods of this class are `insert`, `query`, and `intersect`.
- `insert`
  `insert` simply takes a heap-allocated `Ticket` pointer and places it in each of the maps, using the internal attributes of the pointer.
- `query`
  `query` creates a set of tickets that match the search parameters by taking the intersect of the sets that directly correspond to the search parameters, then creates a by intersecting the directly corresponding sets of the dependent variable, and also all the sets in the maps corresponding to the independent variables.
  Then we return a pair holding the size of the matching parameters set divided by the size of the independent variables set, and the first 8 items from the independent variables set to be displayed in the results screen of the GUI.
- `intersect`
  `intersect` checks which set passed in is smaller, then iterates through it and checks the existence of each element in the larger set, exploiting the `O(log(n))` of `find()` in ordered sets. If the element is in both sets, it inserts into a result set to return.
### BongoHashMap
BongoHashMap is 
