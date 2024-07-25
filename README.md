# Pilapse

A program to use webcams and a Rapsberry Pi to create time lapse videos


## Setting up

SSH into your raspberry pi or open a terminal if using an external monitor set up with your Raspberry Pi

Move to a working directory, something like, `cd ./Documents/`

Clone this repository into your directory:

- with HTTPS: `git clone https://github.com/Johnny-Codes/pilapse.git`

- with SSH: `git clone git@github.com:Johnny-Codes/pilapse.git`

Run this command in terminal:

```
sudo apt-get update
sudo apt-get install libopencv-dev
```


## Compile and Execute

Compile which program you want to use. 

```
gcc -o timelapse_mp4 timelapse_mp4.c `pkg-config --cflags --libs opencv4`
```

Run this in terminal:

```
./<program name> <device number> <capture interval> <total duration>
```

So if using the mp4 file, and you want to capture every 5 seconds for an hour:

```
./timelapse_mp4 0 5 3600
```

Note: If 0 for `<device number>` does not work, try 2 or plugging into another usb slot.


## Optional Streaming

If you want to view your video while setting it up so you can see what's being captured you will need to use mjpg-streamer:

- Install dependencies

```
sudo apt-get update
sudo apt-get install cmake libjpeg8-dev gcc g++ git
```

- Clone the `mjpg-streamer` repo and build it

```
git clone https://github.com/jacksonliam/mjpg-streamer.git
cd mjpg-stramer/mjpg-streamer-experimental
make
sudo make install
```

- Run `mjpg-streamer`:

```
./mjpg_streamer -i "./input_uvc.so" -o "./output_http.so -w ./www"
```

- View in a browser (find your Pi's IP address with `arp-a`. Open a web browser on your phone or local machine that's on the same internet network

```
http://your_pi_ip_address:8080
```

- Press CTRL+C to stop the streaming once the camera is where you want it to be.

## Timelapse Calculator

This is a pretty neat calculator that you can use to figure out `clip length`, `shooting interval`, or `event duration` - https://www.photopills.com/calculators/timelapse
