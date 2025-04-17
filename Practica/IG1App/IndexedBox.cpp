#include "IndexedBox.h"

#include "IndexMesh.h"

IndexedBox::IndexedBox(float l)
{
	mMesh = IndexMesh::generateIndexedBox(l);
}
