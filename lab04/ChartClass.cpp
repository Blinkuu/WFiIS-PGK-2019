#include <wx/dc.h>
#include <memory>

#include "ChartClass.h"
#include "vecmat.h"

#define GRANULARITY 50

ChartClass::ChartClass(std::shared_ptr<ConfigClass> c)
{
    cfg = std::move(c);
    x_step = 200;
}

void ChartClass::Set_Range() const
{
    double xmin = 9999.9, xmax = -9999.9, ymin = 9999.9, ymax = -9999.9;
    double x, y, step;
    int i;

    xmin = cfg->Get_x_start();
    xmax = cfg->Get_x_stop();

    step = (cfg->Get_x_stop() - cfg->Get_x_start()) / (double) x_step;
    x = cfg->Get_x_start();

    for(i = 0; i <= x_step; i++)
    {
        y = GetFunctionValue(x);
        if(y > ymax) ymax = y;
        if(y < ymin) ymin = y;
        x = x + step;
    }

    y_min = ymin;
    y_max = ymax;
    x_min = xmin;
    x_max = xmax;
}


double ChartClass::GetFunctionValue(double x) const
{
    if(cfg->Get_F_type() == 1) return x * x;
    if(cfg->Get_F_type() == 2) return 0.5 * exp(4 * x - 3 * x * x);
    return x + sin(x * 4.0);
}

void ChartClass::Draw(wxDC* dc, int w, int h)
{
    dc->SetBackground(wxBrush(wxColour(*wxWHITE)));
    dc->Clear();
    dc->SetPen(wxPen(wxColour(*wxRED)));
    dc->DrawRectangle(10, 10, w - 20, h - 20);
    dc->SetClippingRegion(11, 11, w, h);
    dc->SetClippingRegion(w - 11, h - 11, -w, -h);
    DrawCoordinateSystem(dc, w, h);
}

void ChartClass::DrawCoordinateSystem(wxDC* dc, int w, int h) const
{
    dc->SetPen(wxPen(wxColour(*wxBLUE)));
    this->w = w;
    this->h = h;
    double xStart = cfg->Get_x_start();
    double xStop = cfg->Get_x_stop();

    Matrix model = GetIdentityMatrix();
    Matrix translation = GetTranslationMatrix(cfg->Get_dX(), cfg->Get_dY());
    Matrix rotation = GetRotationMatrix(cfg->Get_Alpha());

    model = model * translation;

    if(cfg->RotateScreenCenter())
    {
        model = model
                * GetTranslationMatrix(w / 2 - cfg->Get_dX(), h / 2 - cfg->Get_dY())
                * rotation
                * GetTranslationMatrix(-(w / 2 - cfg->Get_dX()), -(h / 2 - cfg->Get_dY()));

        model = model * GetToScreenMatrix(w, h);
    } else
    {
        model = model
                * GetTranslationMatrix(w / 2, h / 2)
                * rotation
                * GetTranslationMatrix(-w / 2, -h / 2);

        model = model * GetToScreenMatrix(w, h);
    }

    line2d(dc, model, xStart, 0, xStop, 0);
    line2d(dc, model, 0, Get_Y_min(), 0, Get_Y_max());

    // Axis (0,0)
    Vector xLegend, yLegend;
    xLegend.Set(0.1, 0);
    yLegend.Set(0, 0.2);
    xLegend = model * xLegend;
    yLegend = model * yLegend;
    dc->DrawRotatedText("0.00", wxPoint(xLegend.GetX(), h - xLegend.GetY()), cfg->Get_Alpha());
    dc->DrawRotatedText("0.00", wxPoint(yLegend.GetX(), h - yLegend.GetY()), cfg->Get_Alpha());

    // X axis
    Vector xAxisPositive, xAxisNegative;
    xAxisPositive.Set(xStop / 2.0, 0);
    xAxisNegative.Set(xStart / 2.0, 0);
    line2d(dc, model, xAxisPositive.GetX(), -0.05, xAxisPositive.GetX(), 0.05);
    line2d(dc, model, xAxisNegative.GetX(), -0.05, xAxisNegative.GetX(), 0.05);
    xAxisPositive = model * xAxisPositive;
    xAxisNegative = model * xAxisNegative;
    dc->DrawRotatedText(std::to_string(xStop / 2.0), wxPoint(xAxisPositive.GetX(), h - xAxisPositive.GetY()),
                        cfg->Get_Alpha());
    dc->DrawRotatedText(std::to_string(xStart / 2.0), wxPoint(xAxisNegative.GetX(), h - xAxisNegative.GetY()),
                        cfg->Get_Alpha());

    // Y axis
    Vector yAxisPositive, yAxisNegative;
    yAxisPositive.Set(0, Get_Y_max() / 2.0);
    yAxisNegative.Set(0, Get_Y_min() / 2.0);
    line2d(dc, model, -0.05, yAxisPositive.GetY(), 0.05, yAxisPositive.GetY());
    line2d(dc, model, -0.05, yAxisNegative.GetY(), 0.05, yAxisNegative.GetY());
    yAxisPositive = model * yAxisPositive;
    yAxisNegative = model * yAxisNegative;
    dc->DrawRotatedText(std::to_string(Get_Y_max() / 2.0), wxPoint(yAxisPositive.GetX(), h - yAxisPositive.GetY()),
                        cfg->Get_Alpha());
    dc->DrawRotatedText(std::to_string(Get_Y_min() / 2.0), wxPoint(yAxisNegative.GetX(), h - yAxisNegative.GetY()),
                        cfg->Get_Alpha());

    // Arrows on axis
    line2d(dc, model, xStop - 0.05, 0.05, xStop, 0);
    line2d(dc, model, xStop - 0.05, -0.05, xStop, 0);

    line2d(dc, model, 0.05, Get_Y_max() - 0.05, 0, Get_Y_max());
    line2d(dc, model, -0.05, Get_Y_max() - 0.05, 0, Get_Y_max());

    // Draw function
    dc->SetPen(wxPen(wxColour(*wxGREEN)));

    double step = (xStop - xStart) / GRANULARITY;
    for(int i = 0; i < GRANULARITY - 1; ++i)
    {
        line2d(dc, model, xStart + i * step, GetFunctionValue(xStart + i * step), xStart + (i + 1) * step,
               GetFunctionValue(xStart + (i + 1) * step));
    }
}

void ChartClass::line2d(wxDC* dc, const Matrix& mat, double x1, double y1, double x2, double y2) const
{
    Vector p1, p2;
    p1.Set(x1, y1);
    p2.Set(x2, y2);

    p1 = mat * p1;
    p2 = mat * p2;

    dc->DrawLine(wxPoint(p1.GetX(), h - p1.GetY()), wxPoint(p2.GetX(), h - p2.GetY()));
}

double ChartClass::Get_Y_min() const
{
    Set_Range();
    return y_min;
}

double ChartClass::Get_Y_max() const
{
    Set_Range();
    return y_max;
}

Matrix ChartClass::GetIdentityMatrix() const
{
    Matrix result;
    result.data[0][0] = 1.0;
    result.data[1][1] = 1.0;

    return result;
}

Matrix ChartClass::GetRotationMatrix(float angle) const
{
    Matrix result;
    angle = M_PI * angle / 180.0f;
    result.data[0][0] = cosf(angle);
    result.data[1][0] = sinf(angle);
    result.data[0][1] = -sinf(angle);
    result.data[1][1] = cosf(angle);

    return result;
}

Matrix ChartClass::GetScaleMatrix(float scaleX, float scaleY) const
{
    Matrix result;

    result.data[0][0] = scaleX;
    result.data[1][1] = scaleY;

    return result;
}

Matrix ChartClass::GetToScreenMatrix(double width, double height) const
{
    double s_x = width / (cfg->Get_x1() - cfg->Get_x0()), s_y = height / (cfg->Get_y1() - cfg->Get_y0());
    Matrix m;
    m.data[0][0] = s_x;
    m.data[0][2] = -s_x * cfg->Get_x0();
    m.data[1][1] = s_y;
    m.data[1][2] = -s_y * cfg->Get_y0();
    return m;
}

Matrix ChartClass::GetTranslationMatrix(float translationX, float translationY) const
{
    Matrix result = GetIdentityMatrix();

    result.data[0][2] = translationX;
    result.data[1][2] = translationY;

    return result;
}





