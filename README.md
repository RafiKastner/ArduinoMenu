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
### Properties 
- content -- 
