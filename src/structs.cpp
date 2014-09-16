#include "structs.h"

ofColor colorFromHsb(colorHsb c) {
    return ofColor::fromHsb(
        256 * c.h,
        256 * c.s,
        256 * c.b
    );
}
