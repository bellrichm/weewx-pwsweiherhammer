<!--prettier-ignore-->
#errorCatcher Echo
#encoding UTF-8
#set diagram_classes = "bx--col-sm-4 bx--col-md-8 bx--col-lg-12 bx--col-xlg-6 bx--col-max-4"
#if $DisplayOptions.get('layout', 'alternative') == 'classic'
  #set diagram_classes = "bx--col-sm-4 bx--col-md-8 bx--col-lg-12 bx--col-xlg-6 bx--col-max-6"
#end if

<div class="$diagram_classes">
  <div class="bx--tile diagram-tile" data-test="$partial_obs">
    <div class="bx--row">
      <div class="bx--col">
        <p class="label">
          <!--prettier-ignore-->
          #if $get_icon($partial_obs) is not None
            #include $get_icon($partial_obs)
          #end if
          $obs.label[$partial_obs]
        </p>
        <div class="value">
          <!--prettier-ignore-->
          #set $series_name = $partial_obs + 'Series' + str($diagram_index)

          <!--prettier-ignore-->
          #if $context == 'month' and $use_parameter_month
          <script>
            /* prettier-ignore */
            var $series_name = $getattr($month, $partial_obs).series(aggregate_type=$get_aggregate_type($partial_obs), aggregate_interval=$get_aggregate_interval($partial_obs, $context, alltime_start=$alltime.start.format('%d.%m.%Y'), alltime_end=$alltime.end.format('%d.%m.%Y')), time_series='both', time_unit='unix_epoch').round($get_rounding($partial_obs)).json;
          </script>
          <!--prettier-ignore-->
          #else if $context == 'year' and $use_parameter_year
          <script>
            /* prettier-ignore */
            var $series_name = $getattr($year, $partial_obs).series(aggregate_type=$get_aggregate_type($partial_obs), aggregate_interval=$get_aggregate_interval($partial_obs, $context, alltime_start=$alltime.start.format('%d.%m.%Y'), alltime_end=$alltime.end.format('%d.%m.%Y')), time_series='both', time_unit='unix_epoch').round($get_rounding($partial_obs)).json;
          </script>
          #else if $context == 'alltime'
          <script>
            /* prettier-ignore */
            var $series_name = $getattr($alltime, $partial_obs).series(aggregate_type=$get_aggregate_type($partial_obs), aggregate_interval=$get_aggregate_interval($partial_obs, $context, alltime_start=$alltime.start.format('%d.%m.%Y'), alltime_end=$alltime.end.format('%d.%m.%Y')), time_series='both', time_unit='unix_epoch').round($get_rounding($partial_obs)).json;
          </script>
          #else if $context == 'yesterday'
          <script>
            /* prettier-ignore */
            var $series_name = $getattr($yesterday, $partial_obs).series(aggregate_type=$get_aggregate_type($partial_obs), aggregate_interval=$get_aggregate_interval($partial_obs, $context, alltime_start=$alltime.start.format('%d.%m.%Y'), alltime_end=$alltime.end.format('%d.%m.%Y')), time_series='both', time_unit='unix_epoch').round($get_rounding($partial_obs)).json;
          </script>
          #else
          <script>
            /* prettier-ignore */
            var $series_name = $getattr($span($hour_delta=$get_hour_delta($context), $boundary=$get_diagram_boundary($context)), $partial_obs).series(aggregate_type=$get_aggregate_type($partial_obs), aggregate_interval=$get_aggregate_interval($partial_obs, $context, alltime_start=$alltime.start.format('%d.%m.%Y'), alltime_end=$alltime.end.format('%d.%m.%Y')), time_series='both', time_unit='unix_epoch').round($get_rounding($partial_obs)).json;
          </script>
          #end if

          <div
            class="diagram"
            data-labels="['$obs.label[$partial_obs]']"
            data-color="['$get_color($partial_obs)']"
            data-value="$series_name"
            data-unit="$getattr($unit.label, $partial_obs)"
            data-obs="$get_diagram_type($partial_obs)"
            data-diagram="$get_diagram($partial_obs)"
            data-context="$context"
            data-aggregate-type="['$get_aggregate_type($partial_obs)']"
            data-nivo-props="$get_nivo_props($partial_obs)"
          ></div>
        </div>
      </div>
    </div>
  </div>
</div>
