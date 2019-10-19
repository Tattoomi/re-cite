open DesignSystem;

let s = React.string;
module Classes = {
  let main =
    Css.(
      style([
        maxWidth(px(700)),
        padding2(~h=px(20), ~v=px(40)),
        margin2(~v=px(0), ~h=`auto),
      ])
    );
};

[@react.component]
let make = () => {
  <main className=Classes.main>
    <article>
      <Heading level=`h1> {s("Primary heading")} </Heading>
      <section>
        <Heading level=`h2> {s("Secondary heading long")} </Heading>
        <Heading level=`h3> {s("Sub heading")} </Heading>
        <Text.Paragraph>
          {s(
             {j|Frustrated with the existing taxonomy of typography in design systems,
        Dan Mall explores different approaches toward making typography in
        design systems more predictable and intuitive. He advocates for
        canonical presets using a numeric system with each preset including
        any combination of properties—size, leading, weight—needed in your
        system. This allows any changes at the preset level to be
        systematically applied to any component that inherits that style.|j},
           )}
        </Text.Paragraph>
        <Heading level=`h3> {s("Tertiary heading")} </Heading>
        <Text.Paragraph>
          {React.string(
             {j|Lorem ipsum dolor sit amet consectetur, adipisicing elit. Quia numquam
        harum cum odio maiores dignissimos beatae facere labore eos accusamus
        nesciunt praesentium, unde fugit blanditiis minima, alias qui
        repudiandae impedit. Error, veritatis? Consequatur optio veniam a fuga
        quos expedita? Odio tenetur nihil id quisquam vitae soluta eveniet,
        harum sunt dolorum, corrupti fugiat officiis. Nesciunt nemo cupiditate
        inventore, voluptates modi dolore blanditiis quidem officiis corporis
        cumque!|j},
           )}
        </Text.Paragraph>
        <Text.Paragraph>
          {React.string(
             {j|Ipsum consequatur rem unde similique esse dignissimos. Quae,
        ut? Ducimus quisquam tempora nemo, possimus, vel ullam hic explicabo,
        optio eos itaque repellendus quibusdam? Exercitationem distinctio,
        esse doloribus eos iure numquam ducimus odio perferendis totam
        obcaecati.|j},
           )}
        </Text.Paragraph>
      </section>
    </article>
  </main>;
};
