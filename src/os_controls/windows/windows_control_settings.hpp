#pragma once

#include "os_control_settings.hpp"

namespace lae {
	class WindowsControlSettings : public OSControlSettings {
		public:
			void init() override;
			void set_cursor_start_position() override;
	};
}
