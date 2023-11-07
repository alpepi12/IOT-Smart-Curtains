# IOT Smart Curtains
<sup>*Undergraduate project for Product Development course (2018).*</sup>


## Project Objectives
Our group was tasked to build, in 10 weeks, a functional prototype of curtains that could be used by a client with reduced mobility. We designed, programmed and built "Smart Curtains" that can be controlled using the client's Google Home device.

## Program Functionality

The ESP Wi-Fi chip is programmed to receive commands from third party IoT services, which are linked with the client's Google Assistant. These commands are relayed to the Arduino board using SPI.<br>
Once a command is transmitted to the Arduino, it verifies the current state of the curtains using ultrasonic distance sensors.  If appropriate, it drives DC motors to move the curtains to the desired state and uses ultrasonic distance sensors to monitor the movement of the curtains.

## Images and Videos

Wiring Diagram:
![image](https://github.com/alpepi12/IOT-Smart-Curtains/assets/91648886/973da852-c21d-49dc-9f56-40bbec8e6345)
<br>

Demonstration Video:
<blockquote class="twitter-tweet"><p lang="en" dir="ltr">Smart blinds allow for both voice/ mobile 🗣 and manual opening and closing. Using an arduino, the functions can be customized to the user. The curtain has sensors to know how extended they are. <a href="https://twitter.com/hashtag/uOttawa?src=hash&amp;ref_src=twsrc%5Etfw">#uOttawa</a> <a href="https://t.co/nuP4bQ91Uv">pic.twitter.com/nuP4bQ91Uv</a></p>&mdash; uOttawa Engineering (@uOttawaGenie) <a href="https://twitter.com/uOttawaGenie/status/1068180832605609985?ref_src=twsrc%5Etfw">November 29, 2018</a></blockquote>
<br>

Awarded the 1<sup>st</sup> place prize in Accessibility category at [uOttawa's Design Day 2018](https://engineering.uottawa.ca/news/genius-ideas-and-ingenious-solutions-design-day).

