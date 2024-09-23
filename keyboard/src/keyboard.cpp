#include "keyboard.h"
#include "ui_keyboard.h"

keyboard::keyboard(QWidget* parent) : QMainWindow(parent), ui(new Ui::keyboard), caps(false), shift(false), lang(false)
{
  setFocusPolicy(Qt::StrongFocus);
  ui->setupUi(this);
  QIcon icon(":/image/images/keyboard.png");
  setWindowIcon(icon);

  connectAllButtons();
  updateCapsLockButtonStyle();
}

keyboard::~keyboard()
{
  delete ui;
}

// void keyboard::keyPressEvent(QKeyEvent *event) {
//     if (event->key() == Qt::Key_A) {
//         // Handle specific key 'A' if needed
//     } else if (event->key() == Qt::Key_Escape) {
//         // Handle specific key 'Escape' if needed
//     } else {
//         qDebug() << "Key pressed:" << event->text();
//     }
// }

// void keyboard::keyReleaseEvent(QKeyEvent *event) {
//     // Handle key release if needed
// }

void keyboard::setButtonStyle(QPushButton* button, const QString& bgColor, const QString& textColor)
{
  button->setStyleSheet(QString("QPushButton { background-color: %1; color: %2; }").arg(bgColor).arg(textColor));
}

void keyboard::on_button_pressed(QPushButton* button)
{
  setButtonStyle(button, "rgb(235, 235, 235)", "rgb(0, 0, 0)");
  if (button == ui->btn42 || button == ui->btn53)
  {
    shift = true;
  }
}

void keyboard::on_button_released(QPushButton* button)
{
  setButtonStyle(button, "rgb(72, 72, 72)", "rgb(255, 255, 255)");
  if (button == ui->btn42 || button == ui->btn53)
  {
    shift = false;
  }
}

void keyboard::connectAllButtons()
{
  QList<QPushButton*> buttons;
  buttons.append(ui->copy);
  buttons.append(ui->clear);
  for (int i = 1; i <= 61; ++i)
  {
    QString buttonName = QString("btn%1").arg(i);
    QPushButton* button = findChild<QPushButton*>(buttonName);
    if (button)
    {
      buttons.append(button);
    }
    else
    {
      //   std::cout << "Button not found:" << buttonName.toStdString() << std::endl;
    }
  }

  for (QPushButton* button : buttons)
  {
    if (button)
    {
      button->setFocusPolicy(Qt::NoFocus);
      connect(button, &QPushButton::pressed, [=]() { on_button_pressed(button); });
      connect(button, &QPushButton::released, [=]() { on_button_released(button); });
      connect(button, &QPushButton::clicked, [=]() { handleButtonClick(button); });
    }
  }
}

void keyboard::handleButtonClick(QPushButton* button)
{
  QString buttonName = button->objectName();
  bool ok;
  int buttonIndex = buttonName.mid(3).toInt(&ok);

  std::vector<std::string> keytexts = lang ? keytext_kor : keytext_eng;

  if (!ok || buttonIndex < 1 || buttonIndex > static_cast<int>(keytexts.size()))
  {
    return;
  }

  std::string text = keytexts[buttonIndex - 1];

  if (text == "Backspace")
  {
    handleBackspace();
  }
  else if (text == "Tab")
  {
    handleTab();
  }
  else if (text == "Enter")
  {
    handleEnter();
  }
  else if (text == "Caps")
  {
    handleCapsLock();
  }
  else if (text == "Shift")
  {
    return;
  }
  else if (text == "Win")
  {
    handleWindows();
  }
  else if (text == "Space")
  {
    handleSpace();
  }
  else if (text == "Kor" || text == "영어")
  {
    return;
  }
  else if (text == "Ctrl" || text == "Alt" || text == "Menu")
  {
    return;
  }
  else
  {
    appendTextToLabel(text);
  }
}

void keyboard::handleBackspace()
{
  QString currentText = ui->textLabel->text();
  currentText.chop(2);
  ui->textLabel->setText(currentText + "_");
}

void keyboard::handleTab()
{
  QString currentText = ui->textLabel->text();
  currentText.chop(1);
  ui->textLabel->setText(currentText + "    " + "_");
}

void keyboard::handleEnter()
{
  QString currentText = ui->textLabel->text();
  currentText.chop(1);
  ui->textLabel->setText(currentText + "\n" + "_");
}

void keyboard::handleCapsLock()
{
  caps = !caps;
  updateCapsLockButtonStyle();
}

void keyboard::handleWindows()
{
#ifdef _WIN32
  INPUT inputs[2] = {};

  inputs[0].type = INPUT_KEYBOARD;
  inputs[0].ki.wVk = VK_LWIN;
  inputs[0].ki.dwFlags = 0;
  inputs[0].ki.wScan = MapVirtualKey(VK_LWIN, MAPVK_VK_TO_VSC);
  inputs[0].ki.time = 0;
  inputs[0].ki.dwExtraInfo = 0;

  inputs[1].type = INPUT_KEYBOARD;
  inputs[1].ki.wVk = VK_LWIN;
  inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
  inputs[1].ki.wScan = MapVirtualKey(VK_LWIN, MAPVK_VK_TO_VSC);
  inputs[1].ki.time = 0;
  inputs[1].ki.dwExtraInfo = 0;

  SendInput(2, inputs, sizeof(INPUT));
#elif __linux__
  Display* display = XOpenDisplay(NULL);
  KeyCode winKey = XKeysymToKeycode(display, XK_Super_L);
  XTestFakeKeyEvent(display, winKey, True, 0);
  XFlush(display);
  XTestFakeKeyEvent(display, winKey, False, 0);
  XFlush(display);
  XCloseDisplay(display);
#endif
}

void keyboard::handleSpace()
{
  QString currentText = ui->textLabel->text();
  currentText.chop(1);
  ui->textLabel->setText(currentText + " " + "_");
}

void keyboard::appendTextToLabel(const std::string& text)
{
  QString textQString = QString::fromStdString(text);
  QStringList parts = textQString.split('\n');

  QString textToAppend;
  if (caps || shift)
  {
    textToAppend = parts.size() > 1 ? parts[0] : parts[0];
  }
  else
  {
    textToAppend = parts.size() > 1 ? parts[1] : parts[0];
  }
  QString currentText = ui->textLabel->text();
  currentText.chop(1);

  ui->textLabel->setText(currentText + textToAppend + "_");
}

void keyboard::updateCapsLockButtonStyle()
{
  setButtonStyle(ui->btn29, caps ? "rgb(235, 235, 235)" : "rgb(72, 72, 72)",
                 caps ? "rgb(0, 0, 0)" : "rgb(255, 255, 255)");
}

void keyboard::setButtonTexts(QList<QPushButton*>& buttons, const std::vector<std::string>& texts)
{
  for (int i = 0; i < buttons.size() && i < texts.size(); ++i)
  {
    buttons[i]->setText(QString::fromStdString(texts[i]));
  }
}

bool keyboard::isCapsLockOn()
{
#if defined(_WIN32)
  return (GetAsyncKeyState(VK_CAPITAL) & 0x0001) != 0;
#elif defined(__linux__)
  Display* display = XOpenDisplay(nullptr);
  if (display == nullptr)
  {
    return false;
  }

  XModifierKeymap* keymap = XGetModifierMapping(display);
  if (keymap == nullptr)
  {
    XCloseDisplay(display);
    return false;
  }

  KeyCode capsLockKeyCode = XKeysymToKeycode(display, XK_Caps_Lock);

  bool isCapsLockOn = false;
  for (int i = 0; i < keymap->max_keypermod; ++i)
  {
    if (keymap->modifiermap[i] == capsLockKeyCode)
    {
      isCapsLockOn = true;
      break;
    }
  }

  XFreeModifiermap(keymap);
  XCloseDisplay(display);

  return isCapsLockOn;
#endif
}

void keyboard::changeLang()
{
  QList<QPushButton*> buttons;
  for (int i = 1; i <= 61; ++i)
  {
    QString buttonName = QString("btn%1").arg(i);
    QPushButton* button = findChild<QPushButton*>(buttonName);
    if (button)
    {
      buttons.append(button);
    }
    else
    {
      //   std::cout << "Button not found:" << buttonName.toStdString() << std::endl;
    }
  }
  std::vector<std::string> keytext = lang ? keytext_eng : keytext_kor;
  lang = !lang;

  setButtonTexts(buttons, keytext);
}

void keyboard::on_btn58_clicked()
{
  changeLang();
}

void keyboard::on_copy_clicked()
{
  QClipboard* clipboard = QApplication::clipboard();
  QString text = ui->textLabel->text();
  clipboard->setText(text);
}

void keyboard::on_clear_clicked()
{
  ui->textLabel->clear();
  ui->textLabel->setText("_");
}
