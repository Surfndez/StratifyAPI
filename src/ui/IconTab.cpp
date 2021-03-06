/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
//Copyright 2011-2018 Tyler Gilbert; All Rights Reserved

#include "ui/IconTab.hpp"
#include "draw.hpp"
using namespace ui;


IconTab::IconTab(){}

void IconTab::draw(const draw::DrawingAttr & attr){
	drawing_point_t p;
	drawing_area_t d;
	DrawingAttr icon_draw_attr;

	d = attr.area();
	p = attr.point();
	Tab::calc_square(p, d);

	icon_draw_attr = attr;
	icon_draw_attr.set_point(p);
	icon_draw_attr.set_area(d);

	icon().draw(icon_draw_attr);
}
