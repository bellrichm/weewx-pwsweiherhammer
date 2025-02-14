<!--prettier-ignore-->
#errorCatcher Echo
#encoding UTF-8
#from datetime import datetime, timedelta
#set $diagrams_config = $DisplayOptions.get("diagrams", {})

<div class="bx--row">
  <!--prettier-ignore-->
  #for $skin_obs in $DisplayOptions.get('stat_tile_observations')
    #if $skin_obs != 'windDir' and $skin_obs != 'windGustDir'
      #if $getattr($get_time_span_from_context($context, $day, $week, $month, $year, $alltime, $yesterday), $skin_obs).has_data
        #set global $partial_obs = $skin_obs
        #include "includes/stat-tile.inc"
      #end if
    #end if
  #end for
</div>

<!--prettier-ignore-->
#if $context == "day"
#include "includes/forecast.inc"
#end if

<div class="bx--row">
  <!--prettier-ignore-->
  <header class="bx--col section-header">
    #if $context == 'day'
      <h2>$gettext("Last 24 hours")</h2>
    #else if $context == 'yesterday'
      <h2>$gettext("Yesterday")</h2>
    #else if $context == 'week'
      <h2>$gettext("Last 7 days")</h2>
      #set $start_date_header = datetime.fromtimestamp($current.dateTime.raw) - timedelta(days=7)
      <h3>
        <!--prettier-ignore-->
        $start_date_header.strftime($get_time_format_dict['week']) - $current.dateTime.format($get_time_format_dict['week'])
      </h3>
    #else if $context == 'month' and not $use_parameter_month
      <h2>$gettext("Last 30 days")</h2>
      #set $start_date_header = datetime.fromtimestamp($current.dateTime.raw) - timedelta(days=30)
      <h3>
        $start_date_header.strftime($get_time_format_dict['month']) - $current.dateTime.format($get_time_format_dict['month'])
      </h3>
    #else if $context == 'month' and $use_parameter_month
      <h2>$month_name $year_name</h2>
    #else if $context == 'year' and not $use_parameter_year
      <h2>$gettext("Last 365 days")</h2>
      #set $start_date_header = datetime.fromtimestamp($current.dateTime.raw) - timedelta(days=365)
      <h3>
        $start_date_header.strftime($get_time_format_dict['year']) - $current.dateTime.format($get_time_format_dict['year'])
      </h3>
    #else if $context == 'year' and $use_parameter_year
      <h2>$year_name</h2>
    #else if $context == 'alltime'
      <h2>$gettext("All Time")</h2>
    #end if
  </header>
</div>

<!-- prettier-ignore -->
<div class="bx--row">
#set $diagram_index = 0
#if "combined_observations" in $diagrams_config
  #set $combined = $diagrams_config.combined_observations
#else
  #set $combined = {}
#end if

#for $skin_obs in $DisplayOptions.get('diagram_tile_observations')
  #if $skin_obs in $combined.keys()
    #set $combined_diagram = $combined[$skin_obs]
    #for $combined_obs in $combined_diagram.obs.keys()
      #if $getattr($get_time_span_from_context($context, $day, $week, $month, $year, $alltime, $yesterday), $combined_diagram.obs[$combined_obs].observation).has_data
        #set global $comb_obs = $skin_obs
        #set global $combined_diagram = $combined_diagram
        #set global $diagram_index = $diagram_index
        #include "includes/combined-diagram-tile.inc"
        #set $diagram_index = $diagram_index + 1
        #break
      #end if
    #end for
  #else
    #if $getattr($get_time_span_from_context($context, $day, $week, $month, $year, $alltime, $yesterday), $skin_obs).has_data or (($skin_obs == 'windDir' or $skin_obs == 'windRose') and $getattr($get_time_span_from_context($context, $day, $week, $month, $year, $alltime, $yesterday), 'windSpeed').has_data)
      #set global $partial_obs = $skin_obs
      #set global $diagram_index = $diagram_index
      #if $skin_obs == 'windRose'
        #include "includes/diagram-tile-wind-rose.inc"
      #else
        #include "includes/diagram-tile.inc"
      #end if
      #set $diagram_index = $diagram_index + 1
    #end if
  #end if
#end for
</div>

#if 'table_tile_observations' in $DisplayOptions
<div class="bx--row">
  <!-- prettier-ignore -->
  #include "includes/data-table-tile.inc"
</div>
#end if
