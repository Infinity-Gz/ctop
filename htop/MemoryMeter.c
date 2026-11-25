/* Modified for ctop container monitoring on 2026-11-25. */
/*
htop - MemoryMeter.c
(C) 2004-2011 Hisham H. Muhammad
Released under the GNU GPLv2, see the COPYING file
in the source distribution for its full text.
*/

#include "MemoryMeter.h"

#include "CRT.h"
#include "Object.h"
#include "Platform.h"
#include "RichString.h"


static const int MemoryMeter_attributes[] = {
   MEMORY_USED,
   MEMORY_BUFFERS,
   MEMORY_CACHE
};

static void MemoryMeter_updateValues(Meter* this, char* buffer, size_t size) {
   int written;
   Platform_setMemoryValues(this);

   written = Meter_humanUnit(buffer, this->values[0] + this->values[1] + this->values[2], size);
   METER_BUFFER_CHECK(buffer, size, written);

   METER_BUFFER_APPEND_CHR(buffer, size, '/');

   if (this->total > 0)
      Meter_humanUnit(buffer, this->total, size);
   else
      xSnprintf(buffer, size, "max");
}

static void MemoryMeter_display(const Object* cast, RichString* out) {
   char buffer[50];
   const Meter* this = (const Meter*)cast;
   RichString_writeAscii(out, CRT_colors[METER_TEXT], ":");
   Meter_humanUnit(buffer, this->total, sizeof(buffer));
   RichString_appendAscii(out, CRT_colors[METER_VALUE], buffer);
   Meter_humanUnit(buffer, this->values[0], sizeof(buffer));
   RichString_appendAscii(out, CRT_colors[METER_TEXT], " used:");
   RichString_appendAscii(out, CRT_colors[MEMORY_USED], buffer);
   Meter_humanUnit(buffer, this->values[1], sizeof(buffer));
   RichString_appendAscii(out, CRT_colors[METER_TEXT], " buffers:");
   RichString_appendAscii(out, CRT_colors[MEMORY_BUFFERS_TEXT], buffer);
   Meter_humanUnit(buffer, this->values[2], sizeof(buffer));
   RichString_appendAscii(out, CRT_colors[METER_TEXT], " cache:");
   RichString_appendAscii(out, CRT_colors[MEMORY_CACHE], buffer);
}

const MeterClass MemoryMeter_class = {
   .super = {
      .extends = Class(Meter),
      .delete = Meter_delete,
      .display = MemoryMeter_display,
   },
   .updateValues = MemoryMeter_updateValues,
   .defaultMode = BAR_METERMODE,
   .maxItems = 3,
   .total = 100.0,
   .attributes = MemoryMeter_attributes,
   .name = "Memory",
   .uiName = "Memory",
   .caption = "Mem"
};
