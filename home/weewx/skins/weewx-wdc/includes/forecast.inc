<!--prettier-ignore-->
#errorCatcher Echo
#encoding UTF-8
#set $forecast_source = $Extras.forecast_table_settings.source
#set $forecast_zambretti_active = True if $varExists('forecast.zambretti') and $to_bool($Extras['forecast_zambretti']['enable']) else False
#set $forecat_table_active = True if $varExists('forecast') and len($forecast.weather_periods($forecast_source)) > 0 else False
#set $dwd_forecast = True if 'weewx-DWD' in $Extras and $to_bool($Extras['weewx-DWD']['show_forecast']) and os.path.exists("dwd/forecast-" + $Extras['weewx-DWD']['mosmix_id'] + ".json") else False
#set $warn_region_front = $Extras['weewx-DWD']['show_warnings_on_front'] if 'weewx-DWD' in $Extras and 'show_warnings_on_front' in $Extras['weewx-DWD'] else False
#set $show_warn = True if $warn_region_front and $dwd_warning_has_warning($warn_region_front) else False

#if ($varExists('forecast') and ($forecast_zambretti_active or $forecat_table_active)) or 'radar_img' in $Extras or $dwd_forecast
<!--prettier-ignore-->

<div class="bx--row">
  <header class="bx--col section-header">
    <h2>
      <!--prettier-ignore-->
      #if $varExists('forecast') or $dwd_forecast
        $gettext("Forecast")
      #end if
      #if ($varExists('forecast') or $dwd_forecast) and 'radar_img' in $Extras
       &
      #end if
      #if 'radar_img' in $Extras
        $gettext($Extras.get("radar_heading", "Recent radar"))
      #end if
    </h2>
  </header>
</div>
<div class="bx--row">
  <div class="bx--col">
    <div class="bx--row">
      <!--prettier-ignore-->
      #if $varExists('forecast') or $dwd_forecast
      #set forecast_tile_classes = "bx--col-sm-4 bx--col-md-8 bx--col-lg-12 bx--col-xlg-6 bx--col-max-8"
      #if $DisplayOptions.get('layout', 'alternative') == 'classic'
        #set forecast_tile_classes = "bx--col-sm-4 bx--col-md-12 bx--col-lg-12 bx--col-xlg-12 bx--col-max-12"
      #end if
      <div class="$forecast_tile_classes">
        <div class="bx--tile forecast-tile">
          <!--prettier-ignore-->
          #if $varExists('forecast.zambretti') and $to_bool($Extras['forecast_zambretti']['enable'])
          <div class="forecast">
            <h3>Zambretti</h3>
            <p>
              <!--prettier-ignore-->
              The forecast is $forecast.label('Zambretti', $forecast.zambretti.code)<br />
              <span class="issued"
                >Issued at $forecast.zambretti.issued_ts</span
              >
            </p>
          </div>
          #end if
          <!--prettier-ignore-->
          #if $varExists('forecast') and not $dwd_forecast
          <div class="forecast">
            <!--prettier-ignore-->
            #include "includes/forecast-table.inc"
          </div>
          #end if
          <!--prettier-ignore-->
          #if $dwd_forecast
          <div class="dwd-forecast forecast">
            <script>
              var dwdForecastData = #include raw "dwd/forecast-" + $Extras['weewx-DWD']['mosmix_id'] + ".json"
            </script>
          </div>
          #end if
        </div>
      </div>
      #end if
      <!--prettier-ignore-->
      #if 'radar_img' in $Extras or $show_warn
      #set radar_classes = "bx--col-sm-4 bx--col-md-8 bx--col-lg-12 bx--col-xlg-6 bx--col-max-4"
      #if $DisplayOptions.get('layout', 'alternative') == 'classic'
        #set radar_classes = "bx--col-sm-4 bx--col-md-12 bx--col-lg-12 bx--col-xlg-12 bx--col-max-12"
      #end if
      <div class="$radar_classes">
        <!--prettier-ignore-->
        #if $show_warn
          #set global $region = $get_dwd_warning_region_name($warn_region_front)
          #set global $region_key = $warn_region_front
          #include "includes/dwd-warning.inc"
        #end if
        #if 'radar_img' in $Extras
        <div class="bx--tile tile-radar-forecast">
          <!--prettier-ignore-->
          #if 'radar_url' in $Extras
          <a href="$Extras.radar_url">
            #end if
            <img src="$Extras.radar_img" alt="Radar" loading="lazy" />
            #if 'radar_url' in $Extras
          </a>
          <!--prettier-ignore-->
          #end if
        </div>
        #end if
      </div>
      #end if
    </div>
  </div>
</div>
#end if
