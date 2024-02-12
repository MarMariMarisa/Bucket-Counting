How to test this!!!!

  1. Download and import files into STM32CudeIDE this was created in version 1.14.1
  2. Attach board to laptop as said previously I utilize a NUCLEO-L476RG
  3. Attach signals into board from your signal generator this reads from port A0
  4. Build from main.c and open a serial port with it. I run on Tera Term COM7, but whatever works for your devices.
  5. Go Ham!!!
    a.If you run a 1KHz signal in and set limits to 950 you should see a range
    b.You can also view a range from running around a 500hz signal in and setting your limits to 1950. May have to lower or raise hz based on your specific device.

![Example Output](/programRunningSuccessFully!!!!.png)
Thanks for reading!!

- Marisa Ortiz 2nd year Software Engineer RIT
