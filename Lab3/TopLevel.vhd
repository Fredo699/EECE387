----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    11:11:16 02/01/2018 
-- Design Name: 
-- Module Name:    TopLevel - Behavioral 
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
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity TopLevel is
    Port ( clk : in  STD_LOGIC;
           SWITCH : in  STD_LOGIC_VECTOR (7 downto 0);
           PWM : out  STD_LOGIC);
end TopLevel;

architecture Behavioral of TopLevel is

signal counter : unsigned(7 downto 0) := to_unsigned(0, 8);
signal sync_clk : std_logic;

component DivideByN is
	 Generic ( N : positive := 64 ); -- N = divide by value
    Port ( clk_in : in  STD_LOGIC;
           clk_out : out  STD_LOGIC := '0');
end component;

begin

process(counter, SWITCH) begin
	if counter < unsigned(SWITCH) then
		PWM <= '1';
	else
		PWM <= '0';
	end if;
end process;

process(sync_clk) begin
	if rising_edge(sync_clk) then
		counter <= counter + to_unsigned(1, 8);
	end if;
end process;

Sync_Clk_Inst : DivideByN
	port map(clk_in=>clk, clk_out=>sync_clk);

end Behavioral;

