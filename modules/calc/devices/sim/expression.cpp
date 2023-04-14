#include "math.h"
#include "expression.h"
#include <algorithm>
#include <chrono>
#include <ctype.h>
#include <iomanip>
#include <random>
#include <string.h>

#define _is_valid_id_char(ch)                                                  \
  (ch && (isalnum(ch) || strchr(".$_", ch) || (char)ch < 0))

static double random_double(double d_min, double d_max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(d_min, d_max);
  return static_cast<double>(dis(gen));
}

static void stringToUpper(std::string &str) {
  std::transform(str.begin(), str.end(), str.begin(),
                 [](char &c) { return std::toupper(c); });
}

static void stringToLower(std::string &str) {
  std::transform(str.begin(), str.end(), str.begin(),
                 [](char &c) { return std::tolower(c); });
}

unsigned char random(double max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dis(0, max);
  return static_cast<double>(dis(gen));
}

static uint64_t MonoTime() {
  auto now = std::chrono::system_clock::now();
  auto nano_time_point =
      std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
  auto epoch = nano_time_point.time_since_epoch();
  uint64_t now_nano =
      std::chrono::duration_cast<std::chrono::nanoseconds>(epoch).count();
  return now_nano;
}


void CExpression::elibmem(arbore a) {
  if (a == 0)
    return;
  if (a->left != 0)
    elibmem(a->left);
  if (a->right != 0)
    elibmem(a->right);
  delete a;
}

CExpression::CExpression() {
  m_Arbore = 0;
  m_definitie = "";
  pozitie = 0;
  error_code = 0;
}

CExpression::~CExpression() { elibmem(m_Arbore); }

int CExpression::UpdateArbore() {
  if (m_definitie.empty())
    return 0;
  elibmem(m_Arbore);
  m_Arbore = 0;
  pozitie = 0;
  m_Arbore = expresie();
  if (m_definitie[pozitie] != '\0') {
    elibmem(m_Arbore);
    m_Arbore = 0;
  }

  if (m_Arbore == 0) {
    return pozitie;
  };
  return -1;
}

CExpression::arbore CExpression::expresie() {
  arbore nod;
  arbore arb1 = termen();
  arbore arb2;
  if (arb1 == 0)
    return 0;

  while ((m_definitie[pozitie] == '-') || (m_definitie[pozitie] == '+')) {
    nod = new NOD;
    nod->left = arb1;
    nod->operatie = m_definitie[pozitie];
    pozitie++;
    arb2 = termen();
    nod->right = arb2;
    if (arb2 == 0) {
      elibmem(nod);
      return 0;
    }
    arb1 = nod;
  }
  return arb1;
}

CExpression::arbore CExpression::termen() {
  arbore nod;
  arbore arb1 = putere();
  arbore arb2;
  if (arb1 == 0)
    return 0;

  while ((m_definitie[pozitie] == '*') || (m_definitie[pozitie] == '/') ||
         (m_definitie[pozitie] == '%')) {
    nod = new NOD;
    nod->left = arb1;
    nod->operatie = m_definitie[pozitie];
    pozitie++;
    arb2 = putere();
    nod->right = arb2;
    if (arb2 == 0) {
      elibmem(nod);
      return 0;
    }
    arb1 = nod;
  }
  return arb1;
}

CExpression::arbore CExpression::putere() {
  arbore nod = 0;
  arbore arb1 = logicalOp();
  arbore arb2;
  if (arb1 == 0)
    return 0;

  while (m_definitie[pozitie] == '^') {
    nod = new NOD;
    nod->left = arb1;
    nod->operatie = m_definitie[pozitie];
    pozitie++;
    arb2 = logicalOp();
    nod->right = arb2;
    if (arb2 == 0) {
      elibmem(nod);
      return 0;
    }
    arb1 = nod;
  }
  return arb1;
}

CExpression::arbore CExpression::factor() {
  arbore nod = 0, nod2 = 0, left = 0;

  while (m_definitie[pozitie] == ' ' && m_definitie[pozitie] != '\0') {
    pozitie++;
  }

  if (m_definitie[pozitie] == '-') {
    nod = new NOD;
    left = new NOD;
    left->right = 0;
    left->left = 0;
    left->operatie = '@';
    left->valoare = -1;
    nod->left = left;
    nod->operatie = '*';
    pozitie++;
    nod->right = expresie();
    if (nod->right == 0)
      return 0;
    return nod;
  }
  if (m_definitie[pozitie] == '(') {
    pozitie++;
    nod = expresie();
    if (nod == 0)
      return 0;
    if (m_definitie[pozitie] != ')') {
      elibmem(nod);
      return 0;
    }
    pozitie++;
    return nod;
  } else
    return identificator();
  return nod;
}

CExpression::arbore CExpression::identificator() {
  int poz;
  arbore nod = 0, nod2 = 0;
  arbore result = 0;

  poz = pozitie;
  SkipSpaces();

  if (m_definitie[pozitie] == '\0')
    result = 0;

  if (isdigit(m_definitie[pozitie])) {
    while ((isdigit(m_definitie[pozitie]) || (m_definitie[pozitie] == '.'))) {
      pozitie++;
    }
    nod = new NOD;
    nod->left = 0;
    nod->right = 0;
    nod->operatie = '@';
    nod->valoare = atof(m_definitie.substr(poz, pozitie - poz).c_str());
    result = nod;
  } else if (_is_valid_id_char(m_definitie[pozitie])) {

    std::string str = m_definitie;
    while (_is_valid_id_char(str[pozitie])) {
      pozitie++;
    }

    std::string id = m_definitie.substr(poz, pozitie - poz);
    std::string nid = id;

    stringToUpper(id);

    if (id == "SIN") {
      nod2 = factor();
      nod = new NOD;
      nod->left = nod2;
      nod->right = 0;
      nod->operatie = 150;
      SkipSpaces();
      return nod;
    } else if (id == "COS") {
      nod2 = factor();
      nod = new NOD;
      nod->left = nod2;
      nod->right = 0;
      nod->operatie = 151;
      SkipSpaces();
      return nod;
    } else if (id == "EXP") {
      nod2 = factor();
      nod = new NOD;
      nod->left = nod2;
      nod->right = 0;
      nod->operatie = 152;
      SkipSpaces();
      return nod;
    } else if (id == "SQRT") {
      nod2 = factor();
      nod = new NOD;
      nod->left = nod2;
      nod->right = 0;
      nod->operatie = 153;
      SkipSpaces();
      return nod;
    } else if (id == "LOG") {
      nod2 = factor();
      nod = new NOD;
      nod->left = nod2;
      nod->right = 0;
      nod->operatie = 154;
      SkipSpaces();
      return nod;
    } else if (id == "TG") {
      nod2 = factor();
      nod = new NOD;
      nod->left = nod2;
      nod->right = 0;
      nod->operatie = 155;
      SkipSpaces();
      return nod;
    } else if (id == "CTG") {
      nod2 = factor();
      nod = new NOD;
      nod->left = nod2;
      nod->right = 0;
      nod->operatie = 156;
      SkipSpaces();
      return nod;
    } else if (id == "ASIN") {
      nod2 = factor();
      nod = new NOD;
      nod->left = nod2;
      nod->right = 0;
      nod->operatie = 157;
      SkipSpaces();
      return nod;
    } else if (id == "ACOS") {
      nod2 = factor();
      nod = new NOD;
      nod->left = nod2;
      nod->right = 0;
      nod->operatie = 158;
      SkipSpaces();
      return nod;
    } else if (id == "ATG") {
      nod2 = factor();
      nod = new NOD;
      nod->left = nod2;
      nod->right = 0;
      nod->operatie = 159;
      SkipSpaces();
      return nod;
    } else if (id == "$YEAR") {
      nod2 = factor();
      nod = new NOD;
      nod->left = nod2;
      nod->right = 0;
      nod->operatie = 160;
      SkipSpaces();
      return nod;
    } else if (id == "$MONTH") {
      nod2 = factor();
      nod = new NOD;
      nod->left = nod2;
      nod->right = 0;
      nod->operatie = 161;
      SkipSpaces();
      return nod;
    } else if (id == "$DAY") {
      nod2 = factor();
      nod = new NOD;
      nod->left = nod2;
      nod->right = 0;
      nod->operatie = 162;
      SkipSpaces();
      return nod;
    } else if (id == "$HOUR") {
      nod2 = factor();
      nod = new NOD;
      nod->left = nod2;
      nod->right = 0;
      nod->operatie = 163;
      SkipSpaces();
      return nod;
    } else if (id == "$MINUTE") {
      nod2 = factor();
      nod = new NOD;
      nod->left = nod2;
      nod->right = 0;
      nod->operatie = 164;
      SkipSpaces();
      return nod;
    } else if (id == "$SECOND") {
      nod2 = factor();
      nod = new NOD;
      nod->left = nod2;
      nod->right = 0;
      nod->operatie = 165;
      SkipSpaces();
      return nod;
    } else if (id == "MAX") {
      SkipSpaces();
      if (m_definitie[pozitie] != '(') {
        return 0;
      }
      pozitie++;
      nod2 = factor();
      // skip ';'
      SkipSpaces();
      if (m_definitie[pozitie] != ',') {
        return 0;
      }
      pozitie++;
      arbore nod3 = factor();
      if (!nod3) {
        return 0;
      }
      SkipSpaces();
      if (m_definitie[pozitie] != ')') {
        return 0;
      };
      pozitie++;
      nod = new NOD;
      nod->left = nod2;
      nod->right = nod3;
      nod->operatie = 166;
      SkipSpaces();
      return nod;
    } else if (id == "MIN") {
      SkipSpaces();
      if (m_definitie[pozitie] != '(') {
        return 0;
      }
      pozitie++;
      nod2 = factor();
      // skip ';'
      SkipSpaces();
      if (m_definitie[pozitie] != ',') {
        return 0;
      }
      pozitie++;
      arbore nod3 = factor();
      if (!nod3) {
        return 0;
      }
      SkipSpaces();
      if (m_definitie[pozitie] != ')') {
        return 0;
      }
      pozitie++;
      nod = new NOD;
      nod->left = nod2;
      nod->right = nod3;
      nod->operatie = 167;
      SkipSpaces();
      return nod;
    } else if (id == "RANDOM") {
      SkipSpaces();
      if (m_definitie[pozitie] != '(') {
        return 0;
      }
      pozitie++;
      nod2 = factor();
      // skip ';'
      SkipSpaces();
      if (m_definitie[pozitie] != ',') {
        return 0;
      }
      pozitie++;
      arbore nod3 = factor();
      if (!nod3) {
        return 0;
      }
      SkipSpaces();
      if (m_definitie[pozitie] != ')') {
        return 0;
      }
      pozitie++;
      nod = new NOD;
      nod->left = nod2;
      nod->right = nod3;
      nod->operatie = 168;
      SkipSpaces();
      return nod;
    } else if (id == "$NOW") {
      nod2 = factor();
      nod = new NOD;
      nod->left = 0;
      nod->right = 0;
      nod->operatie = 169;
      SkipSpaces();
      return nod;
    } else if (id == "LASTUPDATE") {
      nod2 = factor();
      nod = new NOD;
      nod->left = nod2;
      nod->right = 0;
      nod->operatie = 170;
      SkipSpaces();
      return nod;
    } else if (id == "SPAN") {
      nod2 = factor();
      nod = new NOD;
      nod->left = nod2;
      nod->right = 0;
      nod->operatie = 172;
      SkipSpaces();
      return nod;
    } else if (id == "ABS") {
      nod2 = factor();
      nod = new NOD;
      nod->left = nod2;
      nod->right = 0;
      nod->operatie = 173;
      SkipSpaces();
      return nod;
    }
  }
  SkipSpaces();
  return result;
}

int CExpression::ChangeExpression(std::string &expresie) {
  m_definitie = expresie + '\0' + '\0';
  return UpdateArbore();
}

int CExpression::Value(double &valoare) {
  error_code = 0;
  if (m_Arbore == 0)
    return -1;
  valoare = vexp(m_Arbore);
  return (error_code);
}

/**/
double CExpression::vexp(arbore a) {
  double v;

  auto now = MonoTime();
  auto nano = std::chrono::nanoseconds(now);
  std::chrono::system_clock::time_point tp(nano);
  auto time = std::chrono::system_clock::to_time_t(tp);
  struct tm tm;
  localtime_r(&time, &tm);

  if (a->operatie == 0) {
    error_code = 10;
    return 0;
  }
  switch (a->operatie) {
  case '+':
    return (vexp(a->left) + vexp(a->right));
  case '-':
    return (vexp(a->left) - vexp(a->right));
  case '*':
    return (vexp(a->left) * vexp(a->right));
  case '%': {
    v = vexp(a->right);
    if (v == 0) {
      error_code = DIVISION_BY_0;
      return 0;
    }
    return (int)vexp(a->left) % (int)v;
  }
  case '/':
    v = vexp(a->right);
    if (v == 0) {
      error_code = DIVISION_BY_0;
      return -vexp(a->left) / 0.001;
    } else {
      return (vexp(a->left) / v);
    }
  case 150:
    return (sin(vexp(a->left)));
  case 151:
    return (cos(vexp(a->left)));
  case 152:
    return (exp(vexp(a->left)));
  case 153:
    v = vexp(a->left);
    if (v < 0) {
      error_code = INVALID_DOMAIN;
      return 0;
    } else
      return (sqrt(v));
  case 154:
    v = vexp(a->left);
    if (v <= 0) {
      error_code = INVALID_DOMAIN;
      return 0;
    } else
      return (log(v));
  case 155:
    return (tan(vexp(a->left)));
  case 156:
    return (1 / tan(vexp(a->left)));
  case 157:
    return (asin(vexp(a->left)));
  case 158:
    return (acos(vexp(a->left)));
  case 159:
    return (atan(vexp(a->left)));
  case 173:
    return (fabs(vexp(a->left)));
  case 160:
    return tm.tm_year;
  case 161:
    return tm.tm_mon;
  case 162:
    return tm.tm_mday;
  case 163:
    return tm.tm_hour;
  case 164:
    return tm.tm_min;
  case 165:
    return tm.tm_sec;
  case 166:
    return std::max(vexp(a->left), vexp(a->right));
  case 167:
    return std::min(vexp(a->left), vexp(a->right));
  case 168:
    return random_double(vexp(a->left), vexp(a->right));
  case '^':
    return (pow(vexp(a->left), vexp(a->right)));
  case '@':
    return (a->valoare);
  case '<':
    return (vexp(a->left) < vexp(a->right));
  case '>':
    return (vexp(a->left) > vexp(a->right));
  case '!':
    return (!vexp(a->right));
  case '=':
    return (vexp(a->left) == vexp(a->right));
  case '&':
    return (int)(vexp(a->left)) & (int)(vexp(a->right));
  case '|':
    return (int)(vexp(a->left)) | (int)(vexp(a->right));

  case 169: {
    return static_cast<double>(now);
    ;
  }
  }

  return 0;
}

CExpression::arbore CExpression::GetArbore() { return m_Arbore; }

CExpression::CExpression(CExpression &expresie) { *this = expresie; }

CExpression::arbore CExpression::CloneTree() { return clone(m_Arbore); }

CExpression::arbore CExpression::clone(arbore arb) {
  if (arb == 0) {
    return 0;
  }
  arbore clonArb = new NOD;
  *clonArb = *arb;
  clonArb->left = clone(arb->left);
  clonArb->right = clone(arb->right);
  return clonArb;
}

CExpression &CExpression::operator=(CExpression &expr) {
  m_definitie = expr.m_definitie;
  pozitie = 0;
  m_Arbore = expr.CloneTree();
  return *this;
}

void CExpression::SkipSpaces() {
  char c = m_definitie[pozitie];
  while ((c == ' ') && c != '\0') {
    pozitie++;
    c = m_definitie[pozitie];
  };
}

CExpression::arbore CExpression::logicalOp() {
  arbore nod;
  arbore arb1 = sgOp();
  arbore arb2;
  if (arb1 == 0)
    return 0;

  while ((m_definitie[pozitie] == '<') || (m_definitie[pozitie] == '>') ||
         (m_definitie[pozitie] == '=') || (m_definitie[pozitie] == '&') ||
         (m_definitie[pozitie] == '|')) {
    nod = new NOD;
    nod->left = arb1;
    nod->operatie = m_definitie[pozitie];
    pozitie++;
    arb2 = sgOp();
    nod->right = arb2;
    if (arb2 == 0) {
      elibmem(nod);
      return 0;
    }

    arb1 = nod;
  }
  return arb1;
}

CExpression::arbore CExpression::sgOp() {
  arbore nod = 0;
  arbore arb2;
  if ((m_definitie[pozitie] == '!')) {
    nod = new NOD;
    nod->left = 0;
    nod->operatie = m_definitie[pozitie];
    pozitie++;
    arb2 = sgOp();
    nod->right = arb2;
    if (arb2 == 0) {
      elibmem(nod);
      return 0;
    }
  } else {
    nod = factor();
  };
  return nod;
};

bool evaluate(const std::string text, double *val) {
  CExpression expresie;
  std::string s;
  s = text;
  std::remove_if(s.begin(), s.end(), isspace);

  if (expresie.ChangeExpression(s) >= 0) {
    return false;
  }
  if (expresie.Value(*val)) {
    return false;
  }
  return true;
}