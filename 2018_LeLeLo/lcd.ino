void myLcdPrint(String text, int col, int row, boolean clr) {
  if(clr == true) {
    lcd.clear();
  }
  lcd.setCursor(col, row);
  lcd.print(text);
}
