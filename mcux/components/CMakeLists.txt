if(CONFIG_IEEE802154_MCR20A)
  zephyr_include_directories(mcr20a)
endif()

if(CONFIG_ETH_MCUX AND CONFIG_PHY_DP83825)
  zephyr_include_directories(phydp83825)
endif()