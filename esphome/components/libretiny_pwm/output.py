from esphome import pins, automation
from esphome.components import output
import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import (
    CONF_FREQUENCY,
    CONF_ID,
    CONF_PIN,
)

CONFLICTS_WITH = ["esp8266", "esp32", "rp2040"]


def calc_max_frequency(bit_depth):
    return 80e6 / (2**bit_depth)


def calc_min_frequency(bit_depth):
    max_div_num = ((2**20) - 1) / 256.0
    return 80e6 / (max_div_num * (2**bit_depth))


def validate_frequency(value):
    value = cv.frequency(value)
    min_freq = calc_min_frequency(20)
    max_freq = calc_max_frequency(1)
    if value < min_freq:
        raise cv.Invalid(
            f"This frequency setting is not possible, please choose a higher frequency (at least {int(min_freq)}Hz)"
        )
    if value > max_freq:
        raise cv.Invalid(
            f"This frequency setting is not possible, please choose a lower frequency (at most {int(max_freq)}Hz)"
        )
    return value


libretinypwm_ns = cg.esphome_ns.namespace("libretiny_pwm")
LibreTinyPWM = libretinypwm_ns.class_("LibreTinyPWM", output.FloatOutput, cg.Component)
SetFrequencyAction = libretinypwm_ns.class_("SetFrequencyAction", automation.Action)

CONFIG_SCHEMA = output.FLOAT_OUTPUT_SCHEMA.extend(
    {
        cv.Required(CONF_ID): cv.declare_id(LibreTinyPWM),
        cv.Required(CONF_PIN): pins.internal_gpio_output_pin_schema,
        cv.Optional(CONF_FREQUENCY, default="1kHz"): cv.frequency,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    gpio = await cg.gpio_pin_expression(config[CONF_PIN])
    var = cg.new_Pvariable(config[CONF_ID], gpio)
    await cg.register_component(var, config)
    await output.register_output(var, config)
    cg.add(var.set_frequency(config[CONF_FREQUENCY]))


@automation.register_action(
    "output.libretiny_pwm.set_frequency",
    SetFrequencyAction,
    cv.Schema(
        {
            cv.Required(CONF_ID): cv.use_id(LibreTinyPWM),
            cv.Required(CONF_FREQUENCY): cv.templatable(validate_frequency),
        }
    ),
)
async def libretiny_pwm_set_frequency_to_code(config, action_id, template_arg, args):
    paren = await cg.get_variable(config[CONF_ID])
    var = cg.new_Pvariable(action_id, template_arg, paren)
    template_ = await cg.templatable(config[CONF_FREQUENCY], args, float)
    cg.add(var.set_frequency(template_))
    return var
