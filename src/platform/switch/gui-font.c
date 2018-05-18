/* Copyright (c) 2013-2015 Jeffrey Pfau
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "font.h"
#include "icons.h"
#include <mgba-util/gui/font-metrics.h>
#include <mgba-util/gui/font.h>
#include <mgba-util/png-io.h>
#include <mgba-util/vfs.h>

#include <stdlib.h>

#include "nx-gfx.h"

struct GUIFont {
	nxImage font, icons;
	int size;
};

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

struct GUIFont* GUIFontCreate(void) {
	struct GUIFont* guiFont = malloc(sizeof(struct GUIFont));
	if (!guiFont) {
		return 0;
	}

	for (int i = 0; i < 128; i++)
		guiFont->size = MIN(defaultFontMetrics[i].height, guiFont->size);

	guiFont->font.fmt = imgFmtRGBA8;
	guiFont->font.width = 256;
	guiFont->font.height = 128;
	guiFont->font.data = &font[0];

	guiFont->icons.fmt = imgFmtRGBA8;
	guiFont->icons.width = 256;
	guiFont->icons.height = 64;
	guiFont->icons.data = &icons[0];

	return guiFont;
}

void GUIFontDestroy(struct GUIFont* font) {
	free(font);
}

unsigned GUIFontHeight(const struct GUIFont* font) {
	return 16;
}

unsigned GUIFontGlyphWidth(const struct GUIFont* font, uint32_t glyph) {
	if (glyph >= 0 && glyph < 128) {
		// return defaultFontMetrics[glyph].width;
		return 16;
	}
	return 0;
}

void GUIFontIconMetrics(const struct GUIFont* font, enum GUIIcon icon, unsigned* w, unsigned* h) {
	UNUSED(font);
	if (icon >= GUI_ICON_MAX) {
		if (w) {
			*w = 0;
		}
		if (h) {
			*h = 0;
		}
	} else {
		if (w) {
			*w = defaultIconMetrics[icon].width;
		}
		if (h) {
			*h = defaultIconMetrics[icon].height;
		}
	}
}

void GUIFontDrawGlyph(const struct GUIFont* font, int glyph_x, int glyph_y, uint32_t color, uint32_t glyph) {
	if (glyph >= 0 && glyph < 128) {
		struct GUIFontGlyphMetric* metric = &defaultFontMetrics[glyph];

		nxDrawImageEx(glyph_x, glyph_y, ((int)glyph % (font->font.width / 16)) * 16, ((int)glyph / (font->font.width / 16)) * 16, 16, 16, 1, 1, 255, 255, 255, 255, &font->font);
	}
}

void GUIFontDrawIcon(const struct GUIFont* font, int x, int y, enum GUIAlignment align, enum GUIOrientation orient,
                     uint32_t color, enum GUIIcon icon) {
	if (icon >= GUI_ICON_MAX) {
		return;
	}

	struct GUIIconMetric metric = defaultIconMetrics[icon];
	/*switch (align & GUI_ALIGN_HCENTER) {
	case GUI_ALIGN_HCENTER:
		x -= metric.width / 2;
		break;
	case GUI_ALIGN_RIGHT:
		x -= metric.width;
		break;
	}
	switch (align & GUI_ALIGN_VCENTER) {
	case GUI_ALIGN_VCENTER:
		y -= metric.height / 2;
		break;
	case GUI_ALIGN_BOTTOM:
		y -= metric.height;
		break;
	}*/

	nxDrawImageEx(x, y, metric.x, metric.y, metric.width, metric.height, 1, 1, 255, 255, 255, 255, &font->icons);
	/*switch (orient) {
	case GUI_ORIENT_HMIRROR:
	    ctrAddRectEx(color, x + metric.width, y, -metric.width, metric.height, metric.x, metric.y, metric.width,
	                 metric.height, 0);
	    break;
	case GUI_ORIENT_VMIRROR:
	    ctrAddRectEx(color, x, y + metric.height, metric.width, -metric.height, metric.x, metric.y, metric.width,
	                 metric.height, 0);
	    break;
	case GUI_ORIENT_0:
	default:
	    // TODO: Rotation
	    ctrAddRect(color, x, y, metric.x, metric.y, metric.width, metric.height);
	    break;
	}*/
}

void GUIFontDrawIconSize(const struct GUIFont* font, int x, int y, int w, int h, uint32_t color, enum GUIIcon icon) {
	if (icon >= GUI_ICON_MAX) {
		return;
	}

	struct GUIIconMetric metric = defaultIconMetrics[icon];
	/*nxDrawImageEx(x, y, metric.x, metric.y, metric.width, metric.height, MAX(1, w / metric.width),
	              MAX(1, h / metric.height), 255, 255, 255, 255, &font->icons);*/
}
