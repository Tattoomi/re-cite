module Tokens = {
  type color = [
    | `Primary
    | `Secondary
    | `Neutral
    | `BodyBg
    | `BodyText
    | `InputBg
    | `Label
    | `NeutralBorder
    | `ModalBg
  ];

  type fontVariant = [ | `xs | `sm | `md | `lg | `xl | `xxl | `base];

  type fontFamily = [ | `base];

  type spacingScale = [
    | `xxs
    | `xs
    | `sm
    | `md
    | `lg
    | `xl
    | `xxl
    | `xxxl
    | `custom(int)
  ];

  type transitions = [ | `Modal];
};

let rec findMinStep = (test, i) => {
  test(i) ? i : findMinStep(test, i + 1);
};

module Theme = {
  // base values
  let baseFontSizePx = 22;
  let baseLineHeight = 1.4; // 28px

  let baseGridUnit = 4;
  let headingLineHeight = 1.1;
  let fontScale = 1.25;

  let lineHeight = (fontSize, absLineHeight) => {
    let minLineHeight = (fontSize |> float_of_int) *. absLineHeight;
    let isNotLessThanAbs = factor =>
      factor * baseGridUnit |> float_of_int > minLineHeight;

    let factor = findMinStep(isNotLessThanAbs, 1);
    factor * baseGridUnit;
  };

  let toScale = p =>
    Js.Math.pow_float(~base=fontScale, ~exp=p |> float_of_int)
    |> ( *. )(baseFontSizePx |> float_of_int)
    |> int_of_float;

  let numberOfFontVariants = 7;
  let variants =
    Belt.Array.make(numberOfFontVariants, 0)
    ->Belt.Array.mapWithIndex((ind, _) => ind);
  let fontSizes = variants->Belt.Array.map(factor => toScale(factor - 2));

  let bodyLineHeights =
    variants->Belt.Array.map(factor =>
      lineHeight(fontSizes->Belt.Array.getExn(factor), baseLineHeight)
    );
  let headingLineHeights =
    variants->Belt.Array.map(factor =>
      lineHeight(fontSizes->Belt.Array.getExn(factor), headingLineHeight)
    );

  let getLineHeight = (variant, factor) =>
    switch (variant) {
    | `body => bodyLineHeights->Belt.Array.getExn(factor)->Css.px
    | `heading => headingLineHeights->Belt.Array.getExn(factor)->Css.px
    };

  let getSize = ind => fontSizes->Belt.Array.getExn(ind)->Css.px;
  let fontSize =
    fun
    | `xs => getSize(0)
    | `sm => getSize(1)
    | `base => getSize(2)
    | `md => getSize(3)
    | `lg => getSize(4)
    | `xl => getSize(5)
    | `xxl => getSize(6);

  let fontVariant =
    fun
    | `xs => (fontSize(`xs), getLineHeight(`body, 0))
    | `sm => (fontSize(`sm), getLineHeight(`body, 1))
    | `base => (fontSize(`base), getLineHeight(`body, 2))
    | `md => (fontSize(`md), getLineHeight(`body, 3))
    | `lg => (fontSize(`lg), getLineHeight(`heading, 4))
    | `xl => (fontSize(`xl), getLineHeight(`heading, 5))
    | `xxl => (fontSize(`xxl), getLineHeight(`heading, 6));

  let space =
    fun
    | `xxs => 4
    | `xs => 8
    | `sm => 12
    | `md => 16
    | `lg => 24
    | `xl => 32
    | `xxl => 40
    | `xxxl => 48
    | `custom(multiplier) => multiplier * baseGridUnit;

  let color = (token: Tokens.color) =>
    switch (token) {
    | `Primary => "9fd3c7"
    | `Secondary => "9fd3c7"
    | `Neutral => ""
    | `BodyBg => "fcfcfc"
    | `BodyText => "171717"
    | `InputBg => "fff"
    | `NeutralBorder => "ccc"
    | `Label => "555"
    | `ModalBg => "f3f3f3"
    };

  let fontFamily =
    fun
    | `base => "Spectral, serif";

  type transition = {
    duration: int,
    fn: Css_Types.TimingFunction.t,
  };
  let transition =
    fun
    | `Modal => {duration: 300, fn: Css.cubicBesier(0.77, 0.0, 0.175, 1.0)};
};

module Styles = {
  let font = (variant: Tokens.fontVariant) =>
    switch (variant |> Theme.fontVariant) {
    | (font_size, line_height) =>
      Css.[
        fontSize(font_size),
        lineHeight(line_height),
        fontFamily(Theme.fontFamily(`base)),
      ]
    };

  let space = (token: Tokens.spacingScale) => `px(token |> Theme.space);

  let color = (token: Tokens.color) => `hex(token |> Theme.color);

  let animation = (token, name) => {
    let transition = token |> Theme.transition;
    Css.animation(
      ~duration=transition.duration,
      ~timingFunction=transition.fn,
      name,
    );
  };

  let injectGlobal = () => {
    Css.global(
      "body",
      [
        Css.backgroundColor(color(`BodyBg)),
        Css.color(color(`BodyText)),
        ...font(`base),
      ],
    );

    Css.(
      global(
        ".block-scroll",
        [width(pct(100.0)), height(pct(100.0)), overflow(hidden)],
      )
    );
  };

  let toggleBodyScroll = (~disableScroll) => {
    let toggle =
      disableScroll ? DomUtils.addBodyClass : DomUtils.removeBodyClass;
    toggle("block-scroll");
  };
};
