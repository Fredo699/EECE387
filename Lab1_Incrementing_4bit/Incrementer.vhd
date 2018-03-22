----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    11:53:23 01/23/2018 
-- Design Name: 
-- Module Name:    Incrementer - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Incrementer is
    Port ( 	clk : in STD_LOGIC;
				Switch : in  STD_LOGIC;
				LED1 : out  STD_LOGIC_VECTOR (7 downto 4);
				LED2 : out STD_LOGIC_VECTOR (4 downto 0));
end Incrementer;

architecture Behavioral of Incrementer is

signal four : std_logic_vector (3 downto 0);

begin

process(clk)
begin
		
		if rising_edge(clk) then
		
		end if;

end process;

process(Switch)
begin
	
	if Switch = '1' then LED2 <= LED2 + 1;
	end if;

end process;




end Behavioral;

