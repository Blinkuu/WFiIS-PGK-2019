#include "GUIMyFrame1.h"
#include <algorithm>

GUIMyFrame1::GUIMyFrame1(wxWindow* parent)
	:
	MyFrame1(parent)
{
	m_staticText1->SetLabel(_(L"Jasno\u015B\u0107"));
	m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
	this->SetBackgroundColour(wxColor(192, 192, 192));
	m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
	m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

void GUIMyFrame1::m_scrolledWindow_update(wxUpdateUIEvent& event)
{
	Repaint();
}

void GUIMyFrame1::m_b_grayscale_click(wxCommandEvent& event)
{
	Img_Cpy = Img_Org.ConvertToGreyscale();
	m_scrolledWindow->ClearBackground();
	Repaint();
}

void GUIMyFrame1::m_b_blur_click(wxCommandEvent& event)
{
	Img_Cpy = Img_Org.Blur(5);
	m_scrolledWindow->ClearBackground();
	Repaint();
}

void GUIMyFrame1::m_b_mirror_click(wxCommandEvent& event)
{
	Img_Cpy = Img_Org.Mirror();
	m_scrolledWindow->ClearBackground();
	Repaint();
}

void GUIMyFrame1::m_b_replace_click(wxCommandEvent& event)
{
	Img_Cpy = Img_Org.Copy();
	unsigned char* rgb_data = Img_Cpy.GetData();
	int x = Img_Cpy.GetWidth();
	int y = Img_Cpy.GetHeight();

	for (int i = 0; i < x * y * 3; ++i)
	{
		if (rgb_data[i + 0] == 254
			&& rgb_data[i + 1] == 0
			&& rgb_data[i + 2] == 0)
		{
			rgb_data[i + 0] = 0;
			rgb_data[i + 1] = 0;
			rgb_data[i + 2] = 255;
		}
	}

	m_scrolledWindow->ClearBackground();
	Repaint();
}

void GUIMyFrame1::m_b_rescale_click(wxCommandEvent& event)
{
	Img_Cpy = Img_Org.Scale(320, 240);
	m_scrolledWindow->ClearBackground();
	Repaint();
}

void GUIMyFrame1::m_b_rotate_click(wxCommandEvent& event)
{
	Img_Cpy = Img_Org.Rotate(-(30.0 - 180.0) / 360.0, wxPoint{ Img_Org.GetWidth() / 2, Img_Org.GetHeight() / 2 });
	m_scrolledWindow->ClearBackground();
	Repaint();
}

void GUIMyFrame1::m_b_rotate_hue_click(wxCommandEvent& event)
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.RotateHue(0.5);
	m_scrolledWindow->ClearBackground();
	Repaint();
}

void GUIMyFrame1::m_b_mask_click(wxCommandEvent& event)
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.SetMaskFromImage(Img_Mask, 0, 0, 0);
	m_scrolledWindow->ClearBackground();
	Repaint();
}

void GUIMyFrame1::m_s_brightness_scroll(wxScrollEvent& event)
{
	// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
	// Brightness(...), ktora zmienia jasnosc. W tym miejscu nic nie
	// zmieniamy. Do uzupelnienia pozostaje funkcja Brightness(...)
	Brightness(m_s_brightness->GetValue() - 100);
	Repaint();
}

void GUIMyFrame1::m_s_contrast_scroll(wxScrollEvent& event)
{
	// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
	// Contrast(...), ktora zmienia kontrast. W tym miejscu nic nie
	// zmieniamy. Do uzupelnienia pozostaje funkcja Contrast(...)
	Contrast(m_s_contrast->GetValue() - 100);
	Repaint();
}

void GUIMyFrame1::m_b_prewitt_click(wxCommandEvent& event)
{
	// TO DO: Pionowa maska Prewitta
}

void GUIMyFrame1::m_b_threshold_click(wxCommandEvent& event)
{
	Img_Cpy = Img_Org.Copy();
	unsigned char* rgb_data = Img_Cpy.GetData();
	const auto x = Img_Cpy.GetWidth();
	const auto y = Img_Cpy.GetHeight();

	for (auto i = 0; i < x * y * 3; ++i)
	{
		if (rgb_data[i + 0] >= 128)
		{
			rgb_data[i + 0] = 255;
		}
		else
		{
			rgb_data[i + 0] = 0;
		}

		if (rgb_data[i + 1] >= 128)
		{
			rgb_data[i + 1] = 255;
		}
		else
		{
			rgb_data[i + 1] = 0;
		}

		if (rgb_data[i + 2] >= 128)
		{
			rgb_data[i + 2] = 255;
		}
		else
		{
			rgb_data[i + 2] = 0;
		}
	}

	m_scrolledWindow->ClearBackground();
	Repaint();
}

int Truncate(float x)
{
	if (x > 255.0f)
	{
		return 255.0f;
	}
	else if (x < 0.0f)
	{
		return 0.0f;
	}

	return x;
}

void GUIMyFrame1::Contrast(int value)
{
	// TO DO: Zmiana kontrastu obrazu. value moze przyjmowac wartosci od -100 do 100
	float c = (value / 100.0f) * 255.0f;

	Img_Cpy = Img_Org.Copy();
	unsigned char* rgb_data = Img_Cpy.GetData();
	const auto x = Img_Cpy.GetWidth();
	const auto y = Img_Cpy.GetHeight();

	float f = 259.0f * (c + 255.0f) / 255.0f*(259.0f - c);

	for (auto i = 0; i < x * y * 3; ++i)
	{
		rgb_data[i + 0] = Truncate(f * (rgb_data[i + 0] - 128) + 128);
		rgb_data[i + 1] = Truncate(f * (rgb_data[i + 1] - 128) + 128);
		rgb_data[i + 2] = Truncate(f * (rgb_data[i + 2] - 128) + 128);
	}
}

void GUIMyFrame1::Repaint()
{
	wxBitmap bitmap(Img_Cpy); // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
	wxClientDC dc(m_scrolledWindow); // Pobieramy kontekst okna
	m_scrolledWindow->DoPrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
	dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
}

void hsv_to_hsl(double h, double s, double v, double* hh, double* ss, double* ll)
{
	*hh = h;
	*ll = (2 - s) * v;
	*ss = s * v;
	*ss /= (*ll <= 1) ? (*ll) : 2 - (*ll);
	*ll /= 2;
};

void hsl_to_hsv(double hh, double ss, double ll, double* h, double* s, double* v)
{
	*h = hh;
	ll *= 2;
	ss *= (ll <= 1) ? ll : 2 - ll;
	*v = (ll + ss) / 2;
	*s = (2 * ss) / (ll + ss);
};

struct HSL
{
	double h, s, l;
};

HSL rgb_to_hsl(int r, int g, int b) // r,g,b [0, 255]
{
	const double _r = r / 255.0;
	const double _g = g / 255.0;
	const double _b = b / 255.0;

	const double c_max = std::max({ _r, _g, _b });
	const double c_min = std::min({ _r, _g, _b });
	const double delta = c_max - c_min;

	HSL hsl;
	if (delta == 0)
	{
		hsl.h = 0;
	}
	else if (delta == _r)
	{
		hsl.h = 60.0 * (static_cast<int>((_g - _b) / delta) % 6);
	}
	else if (delta == _g)
	{
		hsl.h = 60.0 * (static_cast<int>((_b - _r) / delta) + 2);
	}
	else
	{
		hsl.h = 60.0 * (static_cast<int>((_r - _g) / delta) + 4);
	}

	hsl.l = (c_max + c_min) / 2.0;

	if (delta == 0)
	{
		hsl.s = 0.0;
	}
	else
	{
		hsl.s = delta / (1 - std::abs(2 * hsl.l - 1));
	}

	return hsl;
}

wxImage::RGBValue hsl_to_rgb(const HSL& hsl)
{
	double c = (1 - std::abs(2 * hsl.l - 1)) * hsl.s;
	double x = c * (1 - std::abs(static_cast<int>(hsl.h / 60.0) % 2 - 1));
	double m = hsl.l - c / 2.0;

	wxImage::RGBValue rgb;
	if (hsl.h >= 0.0 && hsl.h < 60.0)
	{
		rgb.red = c;
		rgb.green = x;
		rgb.blue = 0;
	}
	else if (hsl.h >= 60.0 && hsl.h < 120.0)
	{
		rgb.red = x;
		rgb.green = c;
		rgb.blue = 0;
	}
	else if (hsl.h >= 120.0 && hsl.h < 180.0)
	{
		rgb.red = 0;
		rgb.green = c;
		rgb.blue = x;
	}
	else if (hsl.h >= 180.0 && hsl.h < 240.0)
	{
		rgb.red = 0;
		rgb.green = x;
		rgb.blue = c;
	}
	else if (hsl.h >= 240.0 && hsl.h < 300.0)
	{
		rgb.red = x;
		rgb.green = 0;
		rgb.blue = c;
	}
	else
	{
		rgb.red = c;
		rgb.green = 0;
		rgb.blue = x;
	}

	return rgb;
}

void GUIMyFrame1::Brightness(int value)
{
	// TO DO: Zmiana jasnosci obrazu. value moze przyjmowac wartosci od -100 do 100
	Img_Cpy = Img_Org.Copy();
	unsigned char* rgb_data = Img_Cpy.GetData();
	const auto x = Img_Cpy.GetWidth();
	const auto y = Img_Cpy.GetHeight();
	for (auto i = 0; i < x * y * 3; ++i)
	{
		const auto hsv = wxImage::RGBtoHSV(wxImage::RGBValue(rgb_data[i + 0], rgb_data[i + 1], rgb_data[i + 2]));

		double h, s, l;
		double H, S, V;
		hsv_to_hsl(hsv.hue, hsv.saturation, hsv.value, &h, &s, &l);
		l = 0.5 + value / 200.0;
		hsl_to_hsv(h, s, l, &H, &S, &V);

		const auto rgb = wxImage::HSVtoRGB(wxImage::HSVValue{ H, S, V });
		rgb_data[i + 0] = rgb.red;
		rgb_data[i + 1] = rgb.green;
		rgb_data[i + 2] = rgb.blue;
	}
}
