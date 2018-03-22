-- TestBench Template 

  LIBRARY ieee;
  USE ieee.std_logic_1164.ALL;
  USE ieee.numeric_std.ALL;

  ENTITY testbench IS
  END testbench;

  ARCHITECTURE behavior OF testbench IS 

  signal x : integer := 12;
  signal y : integer := 10;
  signal t : integer := 0;

  BEGIN

  --  Test Bench Statements
     tb : PROCESS
     BEGIN
	  
	  wait for 100 ns;
	  
	  y <= x + 2;
	  t <= y;
	  x <= t;

        wait; -- will wait forever
     END PROCESS tb;
  --  End Test Bench 

  END;
