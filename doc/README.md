
# fmt-extra

> Formatters for [**fmt**](https://github.com/LeakyAbstractions/fmt), a tiny C string formatting library

![](https://github.com/LeakyAbstractions/fmt-extra/raw/master/doc/logo.png)

This repository contains some formatters that can be used (together with [**fmt**](https://github.com/LeakyAbstractions/fmt)) to convert objects to custom wide string textual representation.


## API


### Functions

- `format_timespec`: Formats a `timespec` object
- `format_local_datetime`: Formats a `tm` object expressed as Coordinated Universal Time (UTC)
- `format_utc_datetime`: Formats a `tm` object expressed as local time
- `format_ansi`: Emits ANSI escape codes to control SGR (Select Graphic Rendition) parameters
- `format_ansi_color`: Emits ANSI escape codes to control foreground/background color of console text
- `format_ansi_color_reset`: Resets foreground/background color of console text
- `format_bytes`: Formats a number of bytes


## Author

Copyright 2017 [Guillermo Calvo](https://github.com/guillermocalvo)

[![](https://resume.guillermo.in/assets/images/thumb.png)](https://guillermo.in/)


## License

This is free software: you can redistribute it and/or modify it under the terms
of the **GNU Lesser General Public License** as published by the
*Free Software Foundation*, either version 3 of the License, or (at your option)
any later version.

This software is distributed in the hope that it will be useful, but
**WITHOUT ANY WARRANTY**; without even the implied warranty of
**MERCHANTABILITY** or **FITNESS FOR A PARTICULAR PURPOSE**. See the
[GNU Lesser General Public License](http://www.gnu.org/licenses/lgpl.html) for
more details.

You should have received a copy of the GNU Lesser General Public License along
with this software. If not, see <http://www.gnu.org/licenses/>.

### Required

- **License and copyright notice**: Include a copy of the license and copyright
notice with the code.
- **Library usage**: The library may be used within a non-open-source
application.
- **Disclose Source**: Source code for this library must be made available when
distributing the software.

### Permitted

- **Commercial Use**: This software and derivatives may be used for commercial
purposes.
- **Modification**: This software may be modified.
- **Distribution**: You may distribute this software.
- **Sublicensing**: You may grant a sublicense to modify and distribute this
software to third parties not included in the license.
- **Patent Grant**: This license provides an express grant of patent rights from
the contributor to the recipient.

### Forbidden

- **Hold Liable**: Software is provided without warranty and the software
author/license owner cannot be held liable for damages.
