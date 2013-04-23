Pebble Text Watch
=================

On the first launch of Pebble SDK, TextWatch application was not part of the code examples.
Many people wanted to change the texts into their own language and with this app we hope that others will improve it 
and translate it into many more languages.

This watch is a modification of the built in Text Watch face to add date information and to correct the time representation for times that have a spoken zero (10:02 as "ten oh two". First, a short digression on spoken time in english, when the time is spoken at 10:00 as "ten o'clock" the "o'clock" is a contraction of the phrase "of the clock" in contrast to 10:02 where the "oh" is a synonym for "zero".  If one wished to express the spoken zero as a contraction, " 'o " might be appropriate, but "oh" is more common.  Care has been taken to use the same built in fonts for a consistent and clean look and feel.

Versions:

[1] I've added a Date Line at the bottom and corrected times at the top of the hour to read 10:02 as 'ten oh two'.  The weekday is a 2 letter abbreviation.

[2] Weekday and MM.DD are justified to the outside (left and right respectively) and the weekday is abbreviated as 2 or 3 letters depending on rendered width.

[3] A line separator has been added between the time and date.

[4] This is version [1] with the date representation changed to DD.MM for non-US users.  Thanks to James Wigglesworth!


Compiled build of version [3]: https://dl.dropboxusercontent.com/u/11537951/text-watch-date-line.pbw

Screenshot:  
![Text watch screenshot](http://i.imgur.com/cQBVK5c.jpg)
