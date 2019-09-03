## Modifiers

Modifiers change the base value of an attribute depending on 3 different factors.

### Modifier Factors

 ![Factors](img\factors.png)

#### Scalar Increment

Adds a value directly to the attribute.

 ![Scalar Factor](img\factor-scalar.png)

{% hint style='danger' %}
Modifiers should usually be used from a variable (of type *Attr Modifier*) if you want to be able to remove them from Attributes
{% endhint %}

#### Percentage Increment

Adds a percentage of the last value of the attribute.

 ![Percentage Factor](img\factor-pct.png)

 ![Percentage Factor 2](img\factor-pct-2.png)

#### Base Percentage Increment

Similar to Percentage except that this percentage is based on the original value.

 ![Base Percentage Factor](img\factor-base-pct.png)

### Application order

Modifiers are applied into an attribute following the next rules of priority:

1. **Modifier Category** - Check [Modifier Categories](#modifier-categories)

2. **Order** - The order at which modifiers are applied. 

   Adding *"ModA"* and *"ModB"* to the same category will result in *"ModA"* being applied before. 

{% hint style='working' %}
*In a future release: Categories may specify if attributes should apply first last mods on the same category.*
{% endhint %}



## Modifier Categories

Modifier categories are used to specify **modifier application order**. Depending on the genre of a game this can be a key feature that we didn't want to miss.

With a configuration where *"Buff"* is more important than *"Aura"*, a *"Buff"* attribute will be applied before an *"Aura"* modifier.

For example:

![Category Priority](img\category-priority.png)

{% hint style='hint' %}
Categories can also be stored as variables of type *"Attr Category"*
{% endhint %}

### Adding & Removing Categories

Categories can be edited from ***Project Settings -> Game -> Attributes***
Remember, their order matter. First categories are applied first on attributes.

 ![Categories Settings](img\category-settings.png)

{% hint style='danger' %}
Categories **can't** be modified in runtime.
{% endhint %}





