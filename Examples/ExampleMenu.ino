#include <LiquidCrystal.h>
#include <LCDKeypad.h>

#define MAX_ITEM_COUNT 14

LCDKeypad lcd;

bool lcdPressed = false;

class menuScreenBase {
	public:
      bool locked = false;
      bool autoDeselect = true;
      bool displayLast = false;

  		virtual void nextItem() = 0;
  		virtual void previousItem() = 0;
  		virtual void display() = 0;
      virtual void select() = 0;
      virtual void setLocked(bool arg = true) {
        locked = arg;
      };
      virtual void setAutoDeselect(bool arg = true) {
        autoDeselect = arg;
      }
      virtual void setDisplayLast(bool arg = true) {
        displayLast = arg;
      }
  		virtual ~menuScreenBase() {}
}; //just here as a unifier for menuScreen types

template <typename T>
class menuItem {
  private:
  	bool selected = false;
  
  public:
    String content;
  	T* var;
  	T varVal;
  	bool hasVal;

    menuItem(String text, T* var = nullptr, T varVal = T(), bool hasVal = false, bool beginSelected = false) 
      : var(var), varVal(varVal), hasVal(hasVal), selected(beginSelected){
      if (text == "nil" && var != nullptr) {
      	content = String(*var);
        return;
      }
      content = text;
    };
  
 	String displayReturn() {
      return (selected ? "V " : "") + content;
      Serial.println(*var);
    }
  void select(bool arg = true) {
    selected = arg;
    if (hasVal) {
      *var = varVal;
    }
  };
  bool isSelected() {
    return selected;
  }
  void setContent(String text) {
    content = text;
  }

  void printItem() {
    Serial.println(displayReturn());
  };
};

template <typename T>
class menuScreen : public menuScreenBase {
  private:
    size_t size;
    int selectedItemIndex = 0;
  	int currentItemIndex = 0;
    String* contentArr;

  public:
    menuItem<T>* items;
    String text;
    String bottomText; //removed the = "nil" so idk if mess anything up
  
    menuScreen(String text, menuItem<T>* objects, size_t size, String bottomText = "") : items(objects), size(size), text(text), bottomText(bottomText) {
      contentArr = new String[size];
      for (int i = 0; i < size; i++) {
        contentArr[i] = items[i].content;
      }
    }
  
    ~menuScreen() {
      delete[] contentArr;
    }
  
    void display() override {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(text + " " + items[currentItemIndex].displayReturn());
      if (displayLast) {
        lcd.setCursor(0, 1);
        if (size == 1) { return; }
        int newIndex = currentItemIndex - 1;
        if (newIndex < 0) {
          newIndex = size - 1;
        }
        lcd.print(bottomText + " " + items[newIndex].displayReturn());
      }
    }
  
    void nextItem() override {//equivilent to scroll up
      if (size == 1 || locked) { return; }
	  currentItemIndex += 1;
      if (currentItemIndex >= size) {
        currentItemIndex = 0;
      }
      display();
    }
  	void previousItem() override {//equivilent to scroll down
      if (size == 1 || locked) { return; }
	  currentItemIndex -= 1;
      if (currentItemIndex < 0) {
        currentItemIndex = size - 1;
      }
      display();
    }
  
    void showItem(int index) {
      currentItemIndex = index;
      display();
    }

    int contentToIndex(String content) {
      for (int i = 0; i < size; i++) {
        if (contentArr[i] == content) {
          return i;
        }
      }
      return -1;
    }
    void selectItemFromContent(String content, bool deselect = true) {
      int index = contentToIndex(content);
      selectItem(index, deselect);
    }
    void selectItem(int index, bool deselect = true) {
      if (deselect) {
        items[selectedItemIndex].select(false);
      }
      items[index].select(true);
      selectedItemIndex = index;
    }
    void select() override {
      if (locked) {
        return;
      }
      selectItem(currentItemIndex);
    }

    void setAutoDeselect(bool arg) {
      autoDeselect = arg;
    }

    void setLocked(bool arg = true) { //delete?
      locked = arg;
    }

    void printItems() {
      for (int i = 0; i < size; i++) {
        items[i].printItem();
      }
    };
};

class displayType {
  private:
    size_t size;
  public:
    menuScreenBase** screens;
    int currentScreen = 0;

    displayType(menuScreenBase** screens, size_t size) : screens(screens), size(size) {
    };

    void update() {
      screens[currentScreen]->display();
    }
    void next() {
      currentScreen += 1;
      if (currentScreen >= size) {
        currentScreen = 0;
      }
      update();
    }
    void previous() {
      currentScreen -= 1;
      if (currentScreen < 0) {
        currentScreen = size - 1;
      }
      update();
    }

    void select() {
      screens[currentScreen]->select();
    }
  
    void nextItem() {
      screens[currentScreen]->nextItem();
    }
  
    void previousItem() {
      screens[currentScreen]->previousItem();
    }
};


int health = 15;
int ammo = 20;

int someint = 0;
bool somebool = false;

menuItem<int> items_0[] = {
  menuItem<int>("nil", &health, 0, false, false),
  menuItem<int>("nil", &ammo, 0, false, false),
};

menuItem<int> items_1[] = {
  menuItem<int>("1", &someint, 1, true), 
  menuItem<int>("2", &someint, 2, true),
  menuItem<int>("3", &someint, 3, true),
  menuItem<int>("4", &someint, 4, true),
  menuItem<int>("5", &someint, 5, true),
  menuItem<int>("6", &someint, 6, true)
};

menuItem<bool> items_2[] = {
  menuItem<bool>("true", &somebool, true, true),
  menuItem<bool>("false", &somebool, false, true)
};

menuScreen<int> screen_0("Health:", items_0, 2, "Ammo:");
menuScreen<int> screen_1("Nums", items_1, 6);
menuScreen<bool> screen_2("Next", items_2, 2);

menuScreenBase* screens[] = {&screen_0, &screen_1, &screen_2};
displayType display(screens, 3);


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  screen_0.setLocked();
  screen_0.setDisplayLast();
  screen_1.setDisplayLast();
}

void loop() {
  if (lcd.button() == 0) {
    lcdPressed = false;
  }
  else if (!lcdPressed) {
    switch (lcd.button()) {
      case KEYPAD_LEFT:
        display.next();
        lcdPressed = true;
        break;
      case KEYPAD_RIGHT:
        display.previous();
        lcdPressed = true;
        break;
      case KEYPAD_DOWN:
        display.previousItem();
        lcdPressed = true;
        break;
      case KEYPAD_UP:
        display.nextItem();
        lcdPressed = true;
        break;
      case KEYPAD_SELECT:
        lcdPressed = true;
        display.select();
        break;
    }
  } 
}
