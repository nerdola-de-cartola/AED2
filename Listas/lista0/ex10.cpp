#include <iostream>

class RGB {
   public:
      int m_red;
      int m_green;
      int m_blue;

   public:
      RGB();
      RGB(int red, int green, int blue);
      virtual ~RGB();
};

RGB::RGB() 
   : m_red(0), m_green(0), m_blue(0) {}


RGB::RGB(int red, int green, int blue) 
   : m_red(red), m_green(green), m_blue(blue) {}

RGB::~RGB() {}

enum RelativePosition {INSCRITO, DISJUNTOS, CIRCUNSCRITO, COINCIDENTE, TANGENTE, SECANTE, ERROR};

void printRelativePosition(RelativePosition r);

class Circle {
   protected:
      double m_x;
      double m_y;
      double m_radius;
      RGB m_lineColor;
      RGB m_areaColor;
      bool m_visible;

   public:
      Circle(const Circle &c);
      Circle(double x, double y, double radius);
      virtual ~Circle();
      void putLineColor(RGB color);
      void putAreaColor(RGB color);
      void turnVisible();
      void turnInvisible();
      void getCircle(double &x, double &y);
      RGB getLineColor();
      RGB getAreaColor();
      void showCircle();
      double borderRight() const;
      double borderLeft() const;
      double borderTop() const;
      double borderBottom() const;
      RelativePosition getRelativePosition(const Circle &c) const;
};

Circle::Circle(double x, double y, double radius)
   : m_x(x), m_y(y), m_radius(radius), m_lineColor(), m_areaColor(), m_visible(true) {}

Circle::Circle(const Circle &c)
   : m_x(c.m_x), m_y(c.m_y), m_radius(c.m_radius), m_lineColor(c.m_lineColor), m_areaColor(c.m_areaColor), m_visible(c.m_visible) {}
  
Circle::~Circle() {}

void Circle::putLineColor(RGB color) {
   m_lineColor = color;
}

void Circle::putAreaColor(RGB color) {
   m_areaColor = color;
}

void Circle::turnInvisible() {
   m_visible = false;
}

void Circle::turnVisible() {
   m_visible = false;
}

void Circle::getCircle(double &x, double &y) {
   x = m_x;
   y = m_y;
}

RGB Circle::getLineColor() {
   return m_lineColor;
}

RGB Circle::getAreaColor() {
   return m_areaColor;
}

void Circle::showCircle() {
   std::cout << "Centro: (" << m_x << ", " << m_y << ")\n";
   std::cout << "Raio: " << m_radius << '\n';
   std::cout << "Cor da linha: (" << m_lineColor.m_red << ", " << m_lineColor.m_green << ", " << m_lineColor.m_blue << ")\n";
   std::cout << "Cor da area: (" << m_areaColor.m_red << ", " << m_areaColor.m_green << ", " << m_areaColor.m_blue << ")\n";
   if(m_visible) std::cout << "Visível\n";
   else std::cout << "Invisível\n";
}

double Circle::borderRight() const {
   return m_x + m_radius;
}

double Circle::borderLeft() const {
   return m_x - m_radius;
}

double Circle::borderTop() const {
   return m_y + m_radius;
}

double Circle::borderBottom() const {
   return m_y - m_radius;
}


RelativePosition Circle::getRelativePosition(const Circle &c) const {
   if(c.m_radius == m_radius && c.m_x == m_x && c.m_y == m_y) return COINCIDENTE;

   if(
      this->borderRight() < c.borderLeft() ||
      this->borderLeft() > c.borderRight() ||
      this->borderTop() < c.borderBottom() ||
      this->borderBottom() > c.borderTop()
   ) return DISJUNTOS;

   if(
      this->borderRight() < c.borderRight() &&
      this->borderLeft() > c.borderLeft() &&
      this->borderTop() < c.borderTop() &&
      this->borderBottom() > c.borderBottom()
   ) return INSCRITO;

   
   if(
      this->borderRight() > c.borderRight() &&
      this->borderLeft() < c.borderLeft() &&
      this->borderTop() > c.borderTop() &&
      this->borderBottom() < c.borderBottom()
   ) return CIRCUNSCRITO;

   if(
      m_x > c.borderRight() ||
      m_x < c.borderLeft() ||
      m_y > c.borderTop() ||
      m_y < c.borderBottom() ||
      c.getRelativePosition(*this) == SECANTE
   ) return SECANTE;

   return ERROR;
}

void printRelativePosition(RelativePosition r) {
   if(r == INSCRITO) std::cout << "INSCRITO";
   else if(r == DISJUNTOS) std::cout << "DISJUNTOS";
   else if(r == CIRCUNSCRITO) std::cout << "CIRCUNSCRITO";
   else if(r == COINCIDENTE) std::cout << "COINCIDENTE";
   else if(r == TANGENTE) std::cout << "TANGENTE";
   else if(r == SECANTE) std::cout << "SECANTE";
   else if(r == ERROR) std::cout << "ERROR";
}

int main(void) {
   Circle c1(2, 1, 3);
   Circle c2(6, 1, 1);

   c1.showCircle();
   std::cout << std::endl;

   c2.showCircle();
   std::cout << std::endl;

   printRelativePosition(c1.getRelativePosition(c2));
   std::cout << std::endl;

   printRelativePosition(c2.getRelativePosition(c1));
   std::cout << std::endl;

   return 0;
}