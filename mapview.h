/*
   Copyright (c) 2013, Sean Kasun
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef __MAPVIEW_H__
#define __MAPVIEW_H__

#include <QtWidgets/QWidget>
#include "chunkcache.h"
class DefinitionManager;
class BiomeIdentifier;
class BlockIdentifier;

class MapView : public QWidget
{
	Q_OBJECT
public:
	MapView(QWidget *parent=0);

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

	void attach(DefinitionManager *);

	void setLocation(double x,double z);
	void setDimension(QString path,int scale);

public slots:
	void setDepth(int depth);
	void chunkUpdated(int x,int z);
	void redraw();

signals:
	void hoverTextChanged(QString text);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *);
	void wheelEvent(QWheelEvent *event);
	void resizeEvent(QResizeEvent *);
	void paintEvent(QPaintEvent *);

private:

	void drawChunk(int x,int z);
	void renderChunk(Chunk *chunk);
	void getToolTip(int x,int z);

	int depth;
	double x,z;
	int scale;
	double zoom;
	ChunkCache cache;
	QImage image;
	DefinitionManager *dm;
	BlockIdentifier *blocks;
	BiomeIdentifier *biomes;
	uchar placeholder[16*16*4]; // no chunk found placeholder
};

#endif
