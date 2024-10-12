# ArduinoMenu
Class-based structure to create menus for arduino LCD displays
<br>
Also works well woth LCDKeypad library (example in examples folder)

## Install
This is not yet a library, so just copy-paste at the top of your file.

## Usage
Define a variable named lcd with the LCDKeypad or LiquidCrystal library at the top like `LCDKeypad lcd;`

## menuItem
A menuItem is an item in a list that you can scroll through on each screen (aka menuScreen). menuItems belong to menuScreens 
but you can have the same menuItems on different screens. Create in any of the following ways:
<br>
```
menuItem<int>("MyItem);
int num = 1;
menuItem<int> item("nil", num);
menuItem<bool> boolItem("ThisOneIsABoolItem");
```
It's important to note that if you're using an LCD diplay with a low resolution, menuItems may get cut off if their text is too long
<br> 

### Constructor
```
menuItem(String text, Any* var = nullptr, Any varVal = T(), bool hasVal = false, bool beginSelected = false)
```
If text == "nil" then the content is the String() of the var

### Methods
- displayReturn() : string -- returns what the menuItem displays (takes into account selected/deselected symbols)
- select(bool toSetTo) : void -- selects the menuItem. If it has a varVal then it will set the var to the varVal
- isSelected() : void -- returns selected
- setContent(String text) : void -- sets content
- printItem() : void -- Serial.println the displayReturn()

### Properties 
- content : string -- The text that a menuItem displays
- var : any -- A variable that we can change
- varVal : any (same type as var) -- The value we can set the variable to
- hasVal : bool -- Whether or not the menuItem has a varVal we can use
- beginSelected : bool -- To begin selected or not

## menuScreen
A menuScreen contains menuItems. You can scroll through screens as well. You can think of it as screens scroll left/right each containing a vertical list of menuItems.
```
bool somebool = false
menuItem<bool> items[] = {
  menuItem<bool>("true", &somebool, true, true),
  menuItem<bool>("false", &somebool, false, true)
};

menuScreen<bool> screen_0("BoolValue:", items, 2);
```
When assigning menuItems, they **must** be stored in a table that is defined outside the constructor like above. Also, the type of
the menuScreen **must** match with the types of the menuItems. I know this is annoying, but you can only have one type of menuItem per screen. Will maybe
fix in the future.

### Constructor 
```
menuScreen(String text, menuItem<Any>* objects, size_t size, String bottomText = "")
```

### Methods
- display() : void -- Display the screen's text followed by the current menuItem content. If assigned, will do the same for bottomText and the previous item.
- nextItem() : void -- Display the next menuItem in table index order ascending
- previousItem() : void -- Display the previous menuItem
- select() : void -- Selects the current menuItem
- setLocked(bool arg) : void -- Sets the screen to locked or unlocked
- setAutoDeselect(bool arg) : void -- Sets autoDeselect
- setDisplaylast(bool arg) : void -- Sets displayLast
- showItem(int index): void -- Displays the item with that index in the menuItem table
- contentToIndex(String content) : int-- Converts a string content to the index of the item with that content. If multiple items have the same content, whichever has a lower index is returned
- selectItemFromContent(String content, bool deselect) : void -- Selects an item with the given content. Deselects previously selected item if `deselect`
- selectItem(int index) : void -- Selects the item on this screen at that index in the table


### Properties
- text : string -- The text that is displayed on a menuScreen before the text of a menuItem. Would display like `menuText itemText`
- objects : menuItem -- Aka menuItems. This is an array of the menuItems you want assign to the screen
- size : size_t -- How many menuItems you are assigning
- bottomText : string -- Text that displays under the `text`'s text
- locked : bool -- If can scroll through menuItems in the menuScreen
- autoDeselect : bool -- Deselects previously selected item when selecting a new item - i.e. only one item is selected at a time
- displayLast : bool -- Display the previous item on the row below (right after bottomText)

## displayType
The class for the actual display. Everything is contained inside one display. In a sense, a container for all the screens to make everything easier to use.
```
menuScreen<int> screen_0("Health:", items_0, 2, "Ammo:");
menuScreen<int> screen_1("Nums", items_1, 6);
menuScreen<bool> screen_2("Bool", items_2, 2);

menuScreenBase* screens[] = {&screen_0, &screen_1, &screen_2};
displayType display(screens, 3);
```
Again, define the screens table outise of the constructor. Use a pointer for the type like show above.

### Constructor
```
displayType(menuScreenBase** screens, size_t size)
```

### Methods
- update() : void -- Calls `display()` on the current screen
- next() : void -- Displays next screen in ascending order of table index
- previous() : void -- Displays previous screen
- select() : void -- Calls `select()` on current screen
- nextItem() : void -- Calls `nextItem()` on current screen
- previousItem() : void -- Cals `previousItem()` on current screen

### Properties
  - screens : menuScreenBase -- Table containing all the screens
  - size : size_t : Number of screens
