	component SM_MCU is
		port (
			clk_in_clk          : in    std_logic                     := 'X';             -- clk
			reset_in_reset_n    : in    std_logic                     := 'X';             -- reset_n
			sdram_wire_addr     : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_wire_ba       : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_wire_cas_n    : out   std_logic;                                        -- cas_n
			sdram_wire_cke      : out   std_logic;                                        -- cke
			sdram_wire_cs_n     : out   std_logic;                                        -- cs_n
			sdram_wire_dq       : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			sdram_wire_dqm      : out   std_logic_vector(1 downto 0);                     -- dqm
			sdram_wire_ras_n    : out   std_logic;                                        -- ras_n
			sdram_wire_we_n     : out   std_logic;                                        -- we_n
			pio_led_export      : out   std_logic_vector(1 downto 0);                     -- export
			lcd_data_out_export : out   std_logic_vector(15 downto 0);                    -- export
			lcd_rs_export       : out   std_logic;                                        -- export
			lcd_wr_export       : out   std_logic;                                        -- export
			lcd_cs_export       : out   std_logic;                                        -- export
			lcd_rd_export       : out   std_logic;                                        -- export
			lcd_reset_export    : out   std_logic;                                        -- export
			scl_export          : out   std_logic;                                        -- export
			sda_export          : inout std_logic                     := 'X';             -- export
			vs_int_in_export    : in    std_logic_vector(1 downto 0)  := (others => 'X'); -- export
			sm_2strobe_export   : out   std_logic;                                        -- export
			sm_1clr_export      : out   std_logic;                                        -- export
			sm_1ena_export      : out   std_logic;                                        -- export
			sm_mux_export       : out   std_logic_vector(1 downto 0);                     -- export
			sm_data_in_export   : in    std_logic_vector(31 downto 0) := (others => 'X')  -- export
		);
	end component SM_MCU;

	u0 : component SM_MCU
		port map (
			clk_in_clk          => CONNECTED_TO_clk_in_clk,          --       clk_in.clk
			reset_in_reset_n    => CONNECTED_TO_reset_in_reset_n,    --     reset_in.reset_n
			sdram_wire_addr     => CONNECTED_TO_sdram_wire_addr,     --   sdram_wire.addr
			sdram_wire_ba       => CONNECTED_TO_sdram_wire_ba,       --             .ba
			sdram_wire_cas_n    => CONNECTED_TO_sdram_wire_cas_n,    --             .cas_n
			sdram_wire_cke      => CONNECTED_TO_sdram_wire_cke,      --             .cke
			sdram_wire_cs_n     => CONNECTED_TO_sdram_wire_cs_n,     --             .cs_n
			sdram_wire_dq       => CONNECTED_TO_sdram_wire_dq,       --             .dq
			sdram_wire_dqm      => CONNECTED_TO_sdram_wire_dqm,      --             .dqm
			sdram_wire_ras_n    => CONNECTED_TO_sdram_wire_ras_n,    --             .ras_n
			sdram_wire_we_n     => CONNECTED_TO_sdram_wire_we_n,     --             .we_n
			pio_led_export      => CONNECTED_TO_pio_led_export,      --      pio_led.export
			lcd_data_out_export => CONNECTED_TO_lcd_data_out_export, -- lcd_data_out.export
			lcd_rs_export       => CONNECTED_TO_lcd_rs_export,       --       lcd_rs.export
			lcd_wr_export       => CONNECTED_TO_lcd_wr_export,       --       lcd_wr.export
			lcd_cs_export       => CONNECTED_TO_lcd_cs_export,       --       lcd_cs.export
			lcd_rd_export       => CONNECTED_TO_lcd_rd_export,       --       lcd_rd.export
			lcd_reset_export    => CONNECTED_TO_lcd_reset_export,    --    lcd_reset.export
			scl_export          => CONNECTED_TO_scl_export,          --          scl.export
			sda_export          => CONNECTED_TO_sda_export,          --          sda.export
			vs_int_in_export    => CONNECTED_TO_vs_int_in_export,    --    vs_int_in.export
			sm_2strobe_export   => CONNECTED_TO_sm_2strobe_export,   --   sm_2strobe.export
			sm_1clr_export      => CONNECTED_TO_sm_1clr_export,      --      sm_1clr.export
			sm_1ena_export      => CONNECTED_TO_sm_1ena_export,      --      sm_1ena.export
			sm_mux_export       => CONNECTED_TO_sm_mux_export,       --       sm_mux.export
			sm_data_in_export   => CONNECTED_TO_sm_data_in_export    --   sm_data_in.export
		);

