/**********************************************************************************
// Geometry (CÛdigo Fonte)
//
// CriaÁ„o:     05 Oct 2007
// AtualizaÁ„o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// DescriÁ„o:   Agrupa a definiÁ„o de todas as formas geomÈtricas suportadas:
//              ponto, linha, ret‚ngulo, c˙èculo, pol˙Ñono e mista (agrupamento
//              de uma ou mais geometrias)
//
**********************************************************************************/

#include <cmath>
#include "Geometry.h"

// --------------------------------------------------------------------------
// Geometry
// --------------------------------------------------------------------------

Geometry::Geometry()
{ 
    x = y = 0.0f;
    type = UNKNOWN_T; 
}
                                    
// --------------------------------------------------------------------------
    
Geometry::~Geometry()
{
}                


// --------------------------------------------------------------------------
// Point
// --------------------------------------------------------------------------

Point::Point()
{
    type = POINT_T;
}

// --------------------------------------------------------------------------

Point::Point(float posX, float posY)
{
    MoveTo(posX, posY);
    type = POINT_T;
}

// --------------------------------------------------------------------------

Point::Point(int posX, int posY)
{
    MoveTo(float(posX), float(posY)); 
    type = POINT_T;
}

// --------------------------------------------------------------------------

float Point::Distance(const Point & p) const
{
    // acha a dist‚ncia para um outro ponto

    // os deltas podem resultar em valores negativos 
    // para evitar isso pega-se os valores absolutos
    float deltaX = abs(p.X() - x);
    float deltaY = abs(p.Y() - y);

    // calcula e retorna a dist‚ncia
    return sqrt(deltaX*deltaX + deltaY*deltaY);
}

// --------------------------------------------------------------------------
// Line
// --------------------------------------------------------------------------

Line::Line()
{
    // linha padr„o vai de (0,0) atÅE(0,0)
    a = Point();
    b = Point();
    type = LINE_T;
}

// --------------------------------------------------------------------------

Line::Line(float x1, float y1, float x2, float y2)
{
    // cria linha de (x1,y1) atÅE(x2,y2)
    a = Point(x1,y1);    
    b = Point(x2,y2);
    type = LINE_T;
}

// --------------------------------------------------------------------------
    
Line::Line(Point& pa, Point& pb)
{
    // cria linha de pa atÅEpb
    a = pa;
    b = pb;
    type = LINE_T;
}


// --------------------------------------------------------------------------
// Rect  
// --------------------------------------------------------------------------

Rect::Rect()
{
    // cria ret‚ngulo de (0,0) atÅE(0,0)
    left = right  = 0.0f;
    top  = bottom = 0.0f;
    type = RECTANGLE_T;
}

// --------------------------------------------------------------------------

Rect::Rect(float x1, float y1, float x2, float y2)
{
    // cria ret‚ngulo
    left   = x1;
    top    = y1;
    right  = x2; 
    bottom = y2;
    type   = RECTANGLE_T;
}

// --------------------------------------------------------------------------
Rect::Rect(Point& a, Point& b)
{
    // cria ret‚ngulo
    left   = a.X();
    top    = a.Y();
    right  = b.X(); 
    bottom = b.Y();
    type   = RECTANGLE_T;
}

// --------------------------------------------------------------------------
// Circle  
// --------------------------------------------------------------------------

Circle::Circle()
{
    // c˙èculo padr„o tem raio nulo
    radius   = 0;
    type     = CIRCLE_T;
}

// --------------------------------------------------------------------------

Circle::Circle(float r)
{
    // define c˙èculo de raio r
    radius   = r;
    type     = CIRCLE_T;
}

// --------------------------------------------------------------------------
// Poly 
// --------------------------------------------------------------------------

Poly::Poly()
{
    vertexCount = 0;                        // pol˙Ñono n„o tem vÈrtices
    vertexList  = nullptr;                    // inicialmente a lista de vÈrtices ÅEvazia
    type = POLYGON_T;
}

// --------------------------------------------------------------------------

Poly::Poly(Point * vList, uint vCount)
{
    // guarda n˙mero de vÈrtices do pol˙Ñono
    vertexCount = vCount;                    
    
    // aloca memÛria para os vÈrtices
    vertexList = new Point[vCount];    

    // guarda lista de vÈrtices do pol˙Ñono
    for (uint i=0; i < vCount; ++i)        
        vertexList[i].MoveTo(vList[i].X(), vList[i].Y());

    type = POLYGON_T;
}

// --------------------------------------------------------------------------

Poly::Poly(const Poly& p)
{
    // guarda n˙mero de vÈrtices do pol˙Ñono
    vertexCount = p.vertexCount;                    
    
    // aloca memÛria para os vÈrtices
    vertexList = new Point[vertexCount];    

    // guarda lista de vÈrtices do pol˙Ñono
    for (uint i=0; i < vertexCount; ++i)
        vertexList[i].MoveTo(p.vertexList[i].X(), p.vertexList[i].Y());

    type = POLYGON_T;
}

// --------------------------------------------------------------------------

const Poly& Poly::operator=(const Poly& p)
{
    if (vertexList)
        delete [] vertexList;

    // guarda n˙mero de vÈrtices do pol˙Ñono
    vertexCount = p.vertexCount;                    
    
    // aloca memÛria para os vÈrtices
    vertexList = new Point[vertexCount];    

    // guarda lista de vÈrtices do pol˙Ñono
    for (uint i=0; i < vertexCount; ++i)
        vertexList[i].MoveTo(p.vertexList[i].X(), p.vertexList[i].Y());

    type = POLYGON_T;

    return *this;
}

// --------------------------------------------------------------------------

Poly::~Poly()
{
    // libera memÛria alocada para os vÈrtices
    if (vertexList)
        delete [] vertexList;
}


// --------------------------------------------------------------------------
// Mixed 
// --------------------------------------------------------------------------

Mixed::Mixed()
{
    type = MIXED_T;
}

// --------------------------------------------------------------------------

Mixed::~Mixed()
{
    // libera a memÛria ocupa pelas geometrias que compıem essa forma mista
    for (auto i : shapes)
        delete i;
}

// --------------------------------------------------------------------------

void Mixed::Insert(Geometry * s)
{
    shapes.push_back(s);
}

// --------------------------------------------------------------------------

void Mixed::Remove(Geometry * s)
{
    auto i = find(shapes.begin(), shapes.end(), s);
    shapes.erase(i);
}

// --------------------------------------------------------------------------

void Mixed::Translate(float dx, float dy)
{
    x += dx;
    y += dy;

    for (auto i : shapes)
        i->Translate(dx, dy);
}

// --------------------------------------------------------------------------

void Mixed::MoveTo(float px, float py)
{
    for (auto i: shapes)
    {
        float deltaX = i->X() - x;
        float deltaY = i->Y() - y;
        i->MoveTo(px + deltaX, py + deltaY);
    }

    x = px;
    y = py;
}

// --------------------------------------------------------------------------
