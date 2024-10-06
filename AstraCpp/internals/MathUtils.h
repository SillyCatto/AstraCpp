#pragma once

namespace astra::internals::mathutils {

	inline double abs(double x) { return (x < 0) ? -x : x; }

} // namespace astra::internals::mathutils