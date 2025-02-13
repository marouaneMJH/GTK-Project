# GTK3 Tag-Based UI Generator Documentation

## Introduction
This documentation provides an overview of the tag-based system used for generating GTK3 graphical interfaces. Each UI component is defined using tags similar to XML, along with configurable properties to customize their appearance and behavior.

---

## Containers

### `box`
A flexible container for arranging child widgets in a row or column.

| Property            | Possible Values             | Description |
|---------------------|----------------------------|-------------|
| `orientation`      | `"horizontal"`, `"vertical"` | Layout direction |
| `spacing`          | Integer                      | Space between children |
| `homogeneous`      | `"true"`, `"false"`          | Equal space distribution |
| `width`, `height`  | Integer                      | Dimensions in pixels |
| `bg_color`         | Color string                | Background color |
| `text_color`       | Color string                | Text color inside |

### `grid`
A container that organizes widgets in a flexible grid layout.

| Property            | Possible Values       | Description |
|---------------------|----------------------|-------------|
| `column_homogeneous` | `"true"`, `"false"` | Equal column width |
| `row_homogeneous`    | `"true"`, `"false"` | Equal row height |
| `column_spacing`     | Integer             | Space between columns |
| `row_spacing`        | Integer             | Space between rows |
| `bg_color`           | Color string        | Background color |
| `text_color`         | Color string        | Text color inside |
| `margin_top`         | Integer             | Top margin |
| `margin_bottom`      | Integer             | Bottom margin |
| `margin_left`        | Integer             | Left margin |
| `margin_right`       | Integer             | Right margin |

### `fixed`
A container that positions child widgets at fixed coordinates.

| Property            | Possible Values       | Description |
|---------------------|----------------------|-------------|
| `width`, `height`  | Integer              | Dimensions |
| `bg_color`         | Color string         | Background color |
| `text_color`       | Color string         | Text color inside |
| `margin_top`       | Integer              | Top margin |
| `margin_bottom`    | Integer              | Bottom margin |
| `margin_left`      | Integer              | Left margin |
| `margin_right`     | Integer              | Right margin |

---

## Buttons

### `button`
A clickable button widget.

| Property     | Possible Values          | Description |
|-------------|-------------------------|-------------|
| `label`     | String                   | Button text |
| `tooltip`   | String                   | Tooltip on hover |
| `is_sensitive` | `"true"`, `"false"`  | Enabled state |
| `width`, `height` | Integer              | Dimensions |
| `bg_color`  | Color string             | Background color |
| `text_color` | Color string             | Text color |
| `margin_top` | Integer                  | Top margin |
| `margin_bottom` | Integer               | Bottom margin |
| `margin_left` | Integer                 | Left margin |
| `margin_right` | Integer                | Right margin |

---

## Inputs

### `entry`
A text input field.

| Property            | Possible Values  | Description |
|---------------------|-----------------|-------------|
| `placeholder_text`  | String          | Placeholder text |
| `max_length`        | Integer         | Max input length |
| `bg_color`         | Color string    | Background color |
| `text_color`       | Color string    | Text color |
| `margin_top`       | Integer         | Top margin |
| `margin_bottom`    | Integer         | Bottom margin |
| `margin_left`      | Integer         | Left margin |
| `margin_right`     | Integer         | Right margin |

---

## Progress & Indicators

### `progress_bar`
A visual indicator of progress.

| Property            | Possible Values  | Description |
|---------------------|-----------------|-------------|
| `progress_fraction` | Float (0.0 to 1.0) | Fill level |
| `text`             | String          | Displayed text |
| `is_inverted`      | `"true"`, `"false"` | Fill direction |
| `bg_color`         | Color string    | Background color |
| `text_color`       | Color string    | Text color |
| `margin_top`       | Integer         | Top margin |
| `margin_bottom`    | Integer         | Bottom margin |
| `margin_left`      | Integer         | Left margin |
| `margin_right`     | Integer         | Right margin |

---

## Labels & Images

### `label`
A simple text label.

| Property            | Possible Values  | Description |
|---------------------|-----------------|-------------|
| `label_text`       | String          | Displayed text |
| `font_size`       | Integer         | Font size |
| `text_color`       | Color string    | Text color |
| `margin_top`       | Integer         | Top margin |
| `margin_bottom`    | Integer         | Bottom margin |
| `margin_left`      | Integer         | Left margin |
| `margin_right`     | Integer         | Right margin |

### `image`
A widget for displaying images.

| Property            | Possible Values  | Description |
|---------------------|-----------------|-------------|
| `type`             | `"icon"`, `"file"`, `"pixbuf"`, `"animation"`, `"resource"` | Image source type |
| `path`             | String          | Image file path |
| `opacity`          | Float (0.0 to 1.0) | Opacity level |
| `margin_top`       | Integer         | Top margin |
| `margin_bottom`    | Integer         | Bottom margin |
| `margin_left`      | Integer         | Left margin |
| `margin_right`     | Integer         | Right margin |

---

## Notes
- Colors can be defined using named values (`"red"`, `"blue"`) or hex codes (`"#FF0000"`).
- Boolean values are represented as `"true"` or `"false"`.
- Margin properties have been corrected from `mrgin` to `margin`.

This documentation serves as a guide for understanding and using the tag-based system for GTK3 UI generation.

