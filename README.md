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
menuItem<int> item("AnotherItem);
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

### Constructor 
```
menuScreen(String text, menuItem<Any>* objects, size_t size, String bottomText = "")
```

### Methods
- 


### Properties
- text : string -- The text that is displayed on a menuScreen before the text of a menuItem. Would display like `menuText itemText`
- objects : menuItem -- Aka menuItems. This is an array of the menuItems you want assign to the screen
- size : size_t -- How many menuItems you are assigning
- bottomText : string -- Text that displays under the `text`'s text
