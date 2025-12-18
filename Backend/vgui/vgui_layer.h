#pragma once
#include "../qmb/AcceleratedLinkedList.h"
#include "vgui_widget.h"

namespace vgui
{
	using Layer = qmb::AcceleratedLinkedList<Widget>;
}