This payload is triple sensor package hooked up to a Featherboard M0
which handles the computing. The three sensors that are used are:
LIS3DH (accelerometer)
MLX90393 (Magnetometer)
BME680 (Temperature/pressure)

The Mag and the Accel are soldered directly to the board
whereas the BME680 is connected via wires. The main reason for
this is that the detectors couldn't be triple stacked with the
length of header I had available at the time, but it also serves a
scientific purpose, as it leave the potential for the air sensor to be
mounted elsewhere on the rocket.

Measurements are output to the microSD card plugged into the Featherboard
M0. I don't fully understand how the example program converts from the Measurements
to units of micro Tesla based on the gain. I quickly read the crazy datasheet,
and I think the way it works is it just gets one measurement of magnetic
field density, which is spreads out along the axes. So the magnitude of
these numbers should always be meaningful, at least. One thing we can do
to figure this out is to use the event and see what comes out for
multiple gain values, since that's allegedly in units of uT. As I think more about
this, the gain just probably adjusts starting/stop points, just like changing the
acceleration range in the accelerometer example.

The accelerometer is similar to the previous one I used.
I set to +/- 16g. Allegedly the precision is 10 bin, but the output
spans the entire 16 bit range. So that means that 32768, or 2^15 will
be 16g, so that's 32768/16 = 2048/g. That's probably where the 10 bit
precision comes from. When I tested this at +/- 16g, I wasn't getting
the expected 1g. However, maybe that's a precision issue. If I change to
+/- 4g, then 32768/4 = 8192 per g. Sure enough, that was way closer.
OK, so accelerometer ain't gonna be that precise.

The BME680 is pretty straightforward. One confusing thing is what the
gas resistance means that comes off of it. There is some conversion that
they probably use, so once I figure that out, we're good to go.
As long as the number changes, we're still learning something.
ALERT: Turns out this thing is just way way way too slow at making a reading.
Definitely need to make that go faster, or replace the sensor. 
