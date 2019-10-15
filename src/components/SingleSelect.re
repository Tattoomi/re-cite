open Webapi;

type selectOption('item) = {
  item: 'item,
  id: string,
  name: string,
};
let isSelected = (selected, id) =>
  selected->Belt.Option.mapWithDefault(false, s => s == id);

/* let getMenuPlacement = () => {

   } */

module Classes = {
  open Css;
  let root = style([position(relative)]);

  let optionsContainer =
    style([position(absolute), backgroundColor(hex("eee"))]);
};

[@react.component]
let make =
    (
      ~onChange: 'item => unit,
      ~options: array(selectOption('item)),
      ~selectedId: option(string),
    ) => {
  let rootRef = React.useRef(Js.Nullable.null);
  let (isOpen, setIsOpen) = React.useState(() => false);
  let onSelect = option => {
    // setIsOpen(_ => false);
    onChange(option.item);
  };

  // let optionsContainer =
  let body = DomUtils.getBody();
  let position =
    switch (rootRef->React.Ref.current |> Js.Nullable.toOption) {
    | Some(el) => el->Dom.Element.getBoundingClientRect->Some
    | _ => None
    };

  <div
    className=Classes.root
    ref={rootRef->ReactDOMRe.Ref.domRef}
    onBlur={e =>
      switch (rootRef->React.Ref.current |> Js.Nullable.toOption) {
      | Some(el) =>
        let targetElement = ReactEvent.Focus.target(e) |> Obj.magic;

        if (!(el |> Dom.Element.contains(targetElement))) {
          setIsOpen(_ => false);
        };
      | _ => ignore()
      }
    }>
    <button onClick={_ => setIsOpen(_ => true)}>
      {React.string("Select item")}
    </button>
    {switch (isOpen, body, position) {
     | (true, Some(dom), Some(pos)) =>
       ReactDOMRe.createPortal(
         <div
           className=Css.(
             merge([
               Classes.optionsContainer,
               style([
                 top(
                   `px(
                     (pos |> Dom.DomRect.top)
                     +. (pos |> Dom.DomRect.height)
                     |> Js.Math.ceil,
                   ),
                 ),
                 left(`px(pos |> Dom.DomRect.left |> Js.Math.ceil)),
               ]),
             ])
           )>
           <ul tabIndex=(-1)>
             {options->Belt.Array.map(option =>
                <li
                  key={option.id}
                  className={
                    option.id |> isSelected(selectedId) ? "selected" : ""
                  }
                  onClick={_ => onSelect(option)}>
                  {React.string(option.name)}
                </li>
              )
              |> React.array}
           </ul>
         </div>,
         dom,
       )
     | _ => React.null
     }}
  </div>;
};
