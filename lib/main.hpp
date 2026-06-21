#include <Arduino.h>
#include "consts.hpp"
enum NavEvent { NAV_NONE, NAV_UP, NAV_DOWN, NAV_LEFT, NAV_RIGHT, NAV_SELECT, NAV_BACK, NAV_MODE_CHANGE, NAV_SLIDER_JUMP };

enum AppMode { MODE_READING, MODE_BOOK_BROWSER, MODE_SETTINGS };

enum EncoderMode { ENCMODE_SCROLL, ENCMODE_BRIGHTNESS, ENCMODE_BOOK_BROWSER, ENCMODE_SETTINGS_NAV };

struct BookEntry {
  String id;
  String title;
  String author;
};

 struct ReaderState {
  String currentBookId = "";
  int currentPage = 0;
  int encoderMode = 0; // index into EncoderMode
  AppMode mode = MODE_READING;
  BookEntry bookList[BOOKLIST_MAX_ENTRIES];
  int bookListCount = 0;
  int bookListSelectedIdx = 0;
};

