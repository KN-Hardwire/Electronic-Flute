# Electronic Flute Fingering Chart

This document outlines the recognized fingerings for the Electronic flute project. Because this hardware uses simple on/off switches (buttons) instead of acoustic tone holes, acoustic techniques like "half-holing" are not possible. Instead, specific **cross-fingerings** and alternative combinations are hardcoded to produce sharps, flats, and higher register notes.

## Legend
* **⚫** = Button Pressed (Hole Closed)
* **⚪** = Button Unpressed (Hole Open)

*Note: In the hardware logic, a pressed button pulls the GPIO LOW (`0`), and an unpressed button is pulled HIGH (`1`).*

---

## Recognized Note Combinations

Below is the complete list of exact hardware combinations mapped to frequencies. Any "sloppy" finger transitions between these states are banded to the nearest note in the software to prevent glitches.

<table>
  <thead>
	<tr>
	  <th>Note (Intl.)</th>
	  <th style="border-right: 2px solid #777;">Back</th>
	  <th colspan="3" style="border-right: 2px solid #777;">Left Hand</th>
	  <th colspan="4">Right Hand</th>
	</tr>
	<tr>
	  <th></th>
	  <th style="border-right: 2px solid #777;">Thumb</th>
	  <th>Index</th>
	  <th>Middle</th>
	  <th style="border-right: 2px solid #777;">Ring</th>
	  <th>Index</th>
	  <th>Middle</th>
	  <th>Ring</th>
	  <th>Pinky</th>
	</tr>
  </thead>
  <tbody>
	<tr>
	  <td><b>C4</b></td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	</tr>
	<tr>
	  <td><b>C#4 / Db4</b></td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚪</td>
	  <td align="center">⚫</td>
	</tr>
	<tr>
	  <td><b>D4</b></td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚪</td>
	</tr>
	<tr>
	  <td><b>D#4 / Eb4</b></td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚪</td>
	  <td align="center">⚫</td>
	  <td align="center">⚪</td>
	</tr>
	<tr>
	  <td><b>E4</b></td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	</tr>
	<tr>
	  <td><b>F4</b></td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	</tr>
	<tr>
	  <td><b>F#4 / Gb4</b></td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚪</td>
	  <td align="center">⚫</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	</tr>
	<tr>
	  <td><b>G4</b></td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	</tr>
	<tr>
	  <td><b>G#4 / Ab4</b></td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center" style="border-right: 2px solid #777;">⚪</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚪</td>
	</tr>
	<tr>
	  <td><b>A4</b></td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center" style="border-right: 2px solid #777;">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	</tr>
	<tr>
	  <td><b>A#4 / Bb4</b></td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center" style="border-right: 2px solid #777;">⚪</td>
	  <td align="center">⚫</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	</tr>
	<tr>
	  <td><b>B4</b></td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚪</td>
	  <td align="center" style="border-right: 2px solid #777;">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	</tr>
	<tr>
	  <td><b>C5</b></td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚪</td>
	  <td align="center">⚫</td>
	  <td align="center" style="border-right: 2px solid #777;">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	</tr>
	<tr>
	  <td><b>C#5 / Db5</b></td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center" style="border-right: 2px solid #777;">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	</tr>
	<tr>
	  <td><b>D5</b></td>
	  <td align="center" style="border-right: 2px solid #777;">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚫</td>
	  <td align="center" style="border-right: 2px solid #777;">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	</tr>
	<tr>
	  <td><b>D#5 / Eb5</b></td>
	  <td align="center" style="border-right: 2px solid #777;">⚪</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚪</td>
	</tr>
	<tr>
	  <td><b>E5</b></td>
	  <td align="center" style="border-right: 2px solid #777;">⚪</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	</tr>
  </tbody>
</table>

### Alternative Fingerings
These combinations are also recognized by the software to allow for different playing styles or specific trills.

<table>
  <thead>
	<tr>
	  <th>Note (Intl.)</th>
	  <th style="border-right: 2px solid #777;">Back</th>
	  <th colspan="3" style="border-right: 2px solid #777;">Left Hand</th>
	  <th colspan="4">Right Hand</th>
	</tr>
	<tr>
	  <th></th>
	  <th style="border-right: 2px solid #777;">Thumb</th>
	  <th>Index</th>
	  <th>Middle</th>
	  <th style="border-right: 2px solid #777;">Ring</th>
	  <th>Index</th>
	  <th>Middle</th>
	  <th>Ring</th>
	  <th>Pinky</th>
	</tr>
  </thead>
  <tbody>
	<tr>
	  <td><b>C5 (Alt)</b></td>
	  <td align="center" style="border-right: 2px solid #777;">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center" style="border-right: 2px solid #777;">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚪</td>
	</tr>
	<tr>
	  <td><b>B5 (Alt)</b></td>
	  <td align="center" style="border-right: 2px solid #777;">⚪</td>
	  <td align="center">⚪</td>
	  <td align="center">⚫</td>
	  <td align="center" style="border-right: 2px solid #777;">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	  <td align="center">⚫</td>
	</tr>
  </tbody>
</table>

---
**Tip for Builders:** If you are translating these combinations into the raw `button_mask` integer (0-255) for the C array, treat the Thumb as Bit 7 and the Left Index as Bit 0. (e.g., C4 = `0`, D4 = `64`, E4 = `96`, etc.)
