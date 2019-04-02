# Welcome!
I am [Josep Lleal Sirvent](https://www.linkedin.com/in/josep-lleal-sirvent/), student of the
[Bachelor’s Degree in Video Games by UPC at CITM](https://www.citm.upc.edu/ing/estudis/graus-videojocs/). 
This content is generated for the second year’s subject Project 2, under supervision of lecturer
[Ricard Pillosu](https://es.linkedin.com/in/ricardpillosu).

  - Github account: [Josep Lleal](https://github.com/JosepLleal)
  
I understand that if you are reading this is because you are interested in this topic, one of the cores of the [MMORPGs](https://en.wikipedia.org/wiki/Massively_multiplayer_online_role-playing_game) genre. Before I start explaining how to implement a Buff Manager with C++, it is essential to clearly understand how do Buffs work and to know all the different existing types. So, with this being said, lets start:
  
# What is a Buff? 
Before explaining what a Buff really is, I want to introduce the therm **status effect**:

"A **status effect** is a modification to a game character’s original set of stats that usually comes into play when special powers and abilities are used. The term **status effect** can be applied both to changes that provide a character an advantage (increased attributes, defensive barriers, regeneration), and those that hinder the character (decreased attributes, incapability, degeneration)." *Wikipedia*

With this definition we can clearly distinguish two types of status effects, the ones that provide an **advantage** and the others that provide a **disadvantage**:

- **Buff:** is the status effect that affects an entity in a positive way, providing him an advantage. One of the most used buffs in video games is the health potion, which increases the current health of a character.    

<p align="center">
  <img  src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/healing.gif" width="480" height="300">
</p>
<p align="center">
  <i>Healing in Apex Legends</i>
</p>

- **Debuff:** is the status effect that affects an entity in a negative way, providing him a disadvantage. For instance, a commonly used debuff in video games is the poison, which decreases the current health  of a character. 

<p align="center">
  <img  src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/poison.gif" width="480" height="300">
</p>
<p align="center">
  <i>Poison affecting Apex Legends players</i>
</p>

***

# Types of effects
When talking about types of effects the most commonly classification is dividing them into two main groups: buffs and debuffs, as I stated before, but indeed, we can organize them in different ways depending on how we approach them. For instance, the classification of buffs and debuffs is approached by looking **how an effect affects an entity**. The other approaches are looking the **durability of an effect** and **how an effect is applied**(referring to the mathematical method used).

## Durability of an effect
When looking at the durability of an effect we can classify them in four groups: **temporary**, **per tick**, **permanent** and **conditional** effects.

- **Temporary effects**: as the name suggests, this type of effect only remains for a specific amount of time, this means that when the effect is finished all the upgraded attributes will be reverted to its original values. For instance, Janna (a champion from [*League of Legends*](https://eune.leagueoflegends.com/en/game-info/)) has an ability called *Eye of the Storm* that shields the target allied champion or herself for 5 seconds and also gaining bonus attack damage.
<p align="center">
  <img src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/jannashield.gif" width="480">
</p>
<p align="center">
  <i> Janna Eye of the Storm ability </i>
</p>

- **Per tick effects**: this type of effect could be categorized as a subgroup of temporary effects since they last for a limited amount of time, however, per tick effects have a distinctive feature as the attributes are upgraded, usually, every second. In addition, the upgraded stats will not be reverted once the effect finishes. Per tick effects are mainly used for potions and poisons, for example: [health potions](https://leagueoflegends.fandom.com/wiki/Health_Potion) from *League of Legends* which regenerates 5 health every half-second for 15 seconds, restoring a total of 150 health.
<p align="center">
  <img src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/potion.gif" width="480">
</p>
<p align="center">
  <i> Health potion healing League of Legends champion</i>
</p>

- **Permanent effects**: unlike temporary effects, permanent effects will always be active, however, in some games this type of effect is removed when the entity dies. For instance, there are multiple champions in *League of Legends* that have a permanent buff called [*passive*](https://leagueoflegends.fandom.com/wiki/Passive).
<p align="center">
  <img src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/nasus_passive.png" width="480">
</p>
<p align="center">
  <i> <a href="https://leagueoflegends.fandom.com/wiki/Nasus">Nasus</a> passive </i>
</p>

- **Conditional effects**: this type of effect could be categorized as a subgroup of permanent effects as their active time is not limited by any timer. A conditional effect has a condition associated with it and while this condition is fulfilled, the buff will be active. For instance, [Garen](https://leagueoflegends.fandom.com/wiki/Garen)'s passive: Garen passively regenerates 0.2/0.8% (based on level) of his maximum health every half-second and is doubled while below 25/50% of health (based on level) of his maximum health. However, this buff is interrupted for 9/4 seconds (based on level) if he takes non-minion damage or if he is hit by an enemy ability (for this effect, the condition associated to it will be the following: *if Garen hasn't been atacked for 9 or 4 seconds (depending on level)*).

<p align="center">
  <img src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/GarenP.gif" width="480">
</p>
<p align="center">
  <i> Garen's passive </i>
</p>
<p align="center">
  <i> Notice that in this case Garen's passive is a mixture of a per tick and conditional effect </i>
</p>

## Method used
If we approach effects looking how these are applied mathematically to the stats of an entity, we can classify them in three types: Effect applied **by adding**, **by multiplying** and **by adding a percentage**.

- **By adding**: this type of effect adds or substracts (depending if it is a buff or a debuff) an specific amount to an attribute.  
- **By multiplying**:this type of effect multiplies or divides (depending if it is a buff or a debuff) an specific amount to an attribute.
- **By adding a percentage**: this type of effect adds or substracts (depending if it is a buff or a debuff) a determined percentage of the attribute to upgrade. 

***

# Buff Manager implementation
Well, now that the topic has been properly introduced, let’s head to a very simple implementation of a **Buff manager**. Our goal is simple, create effects with XML, read and pass them into code and apply them correctly.

## Creation of effects
The first step to do in order to create effects is to create an **struct** containing all the data that an effect will need: 



```c++
struct Effect 
{
	std::string		name;

	EffectType		type;
	EffectTime		duration_type;
	EffectMethod		method;
	Attribute		attribute_to_change; 

	int			bonus;
	int			duration_value;
};
```

- **name**: it is a string that will contain the **name of the effect**.
- **type**: it is an *EffectType* (enum) variable that can be a *BUFF* or a *DEBUFF*.
- **duration_type**: it is an *EffectType* (enum) variable that can be *PERMANENT*, *TEMPORARY* or *PER_TICK*.
- **method**: it is an *EffectMethod* (enum) variable that can be *ADD*, *MULTIPLY* or *PERCENTAGE*.
- **attribute_to_change**: is the **type of attribute that the effect will modify**. In my case I made an enum called *Attribute* that can be this 4 types: *HEALTH*, *STRENGTH*, *ARMOR* or *SPEED*.
- **bonus**: an integer variable that means: in case the *method* is *ADD* it is the amount that will be added to the desired attribute, in case is *MULTIPLY* it is the amount that will be multiplied and in case is *PERCENTAGE* it is the percentage of the attribute to change.
- **duration_value**: an integer variable that stores the **amount of time in seconds** that an effect will last. If the *duration_type* is  *PERMANENT* this variable is useless.


### XML File
To create one or more effects with an XML file this structure has to be followed:
```c++
<?xml version="1.0" encoding="utf-8"?>
<buff_manager>
  
  <effect id ="0" name="healing" type="BUFF" duration_type="PERMANENT" method="ADD" att_to_change="HEALTH" bonus="20" duration_value="0"></effect>

</buff_manager>
```
As we can see, all the variables are the same as the ones in the effect struct... Oh wait! There is a variable called *id*, what's that?
Ok, calm down, just for now the only thing you need to know about this variable is that whenever a new effect is created in this file, the new effect id will be *latest effect id + 1*. So for instance if we want to create a new effect, his id would be 1 (0+1).  

## Read XML File & Store Effects
In order to read the XML file I have made a function called *LoadEffect()*. This function basically iterates all the *< effect >* nodes and stores all his attributes in a temporary Effect created in the same function. Once all the variables of the effect are set, we store this effect in an array called *effects* (created in the *BuffManager.h*). Remember that *id* I talked about? This is the moment to use it! To store the effect in the array we will do the following: *effects*[*new_effect_id*] = *new_effect*;  

***IMPORTANT:*** with all the *enum-type* variables of the effect, in order to set properly their type I have created a function called *SetValue(&effect, string)* that basically "converts" the string passed into the corresponding *enum-type*.  

<details> 
  <summary>Click here to see the function (IF YOU HAVEN'T DONE THE TODO's DO NOT CLICK)</summary>
  <p> 
	<img src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/LoadEffect.png">
  </p>
</details>

## Apply Effect to an Entity
Before I start explaining how to apply an effect, I'm going to explain **briefly** two things: **how to acces to the desired effect** (without having to remember each effect's id) and **how to "manage" effect's timers and attributes** of an **entity**.

### Acces to desired Effect
Let's say, for instance, that you have created 4 effects that are stored in the *effects* array. If you want to acces to the third created effect you would do this *effects[2]*. But what if you had 20 effects? it would be pretty tough to remember each effect position, right? Be happy, there is a simple solution! 

In *BuffManager.h* I have created an enum called Effects. Each time you create a new effect from the XML, go to this enum and put the effect's name (it is essential to put all the effects in the same order as the XML). So now, to acces to the desired effect just do this: *effects[EFFECT_NAME]*.


### Entity's Attributes & Timers

**ATTRIBUTES:**

For the **attributes** there is only one thing to remark, each attribute has two integer variables: the **original value** and the **actual value**.  
- **original value**: This variable has to only be modified when we apply a *PERMANENT* or *PER_TICK* effect. The main utility of this variable is to reset the **actual value** of an attribute to his **original value** when a *TEMPORARY* effect ends.
- **actual value**: As the name suggests, this is the actual value of the attribute. This variable is **always modified** when we apply **any type of effect**. 


**TIMERS:**

We will need to create a timer for every *TEMPORARY* and *PER_TICK* effect. In addition, we will also create a *boolean* to check if the effect is active or not. For a *PER_TICK* effect, we will create an *integer* that will be used to upgrade an attribute each tick.   

*See these two effects examples to help the understanding:*

```c++
//POISON --- PER TICK EFFECT --- reduces live each tick
j1Timer		poison_tick;
bool		poison_tick_active = false; 
int		poison_tick_iterator = 0;

// WAR CRY --- TEMPORARY --- gain extra strength for a limited time
j1Timer		war_cry;
bool		war_cry_active = false;
```
### How to Apply our effects?

To apply effects I have created two main functions: ***ApplyEffect()*** and ***DoMath()***. *ApplyEffect()* is the function that you will call when applying an effect and *DoMath()* is the responsible, as his name says, to do all the operations. This second function is called inside *ApplyEffects()*.

When calling the function ***ApplyEffects()*** you will need to pass two parameters: the **effect** you want to apply and to which **entity**, so for instance, it would look something like this: *ApplyEffects(&effects[EFFECT_NAME], Entity);*

I'm not going to explain entirely how *ApplyEfefcts()* works but I do have to **remark a few things**:

*ApplyEffect()* firstly checks the *duration_type [PERMANENT, TEMPORARY or PER_TICK]* of the effect and depending on the type it does different things. For *PERMANENT* effects is 100% automatic, however for the other **two types that require a timer** the function has to be updated every time a new effect is created.

See this 2 pieces of code inside *ApplyEffect()* to understand it clearly:

```c++
else if (effect->duration_type == TEMPORARY) // we have to put manually every NEW EFFECT that has a TIMER (and create the timer in entity.h or in this case in Player.h)
	{
		switch (effect->attribute_to_change) // check what attribute modifies
		{
		case HEALTH:
			if (effect->name == effects[HEAL].name)
			{
				if (entity->heal_active == false)
				{
					DoMath(entity->health, effect->bonus, effect->method, effect->type);
					entity->heal_active = true;
				}
				entity->healing.Start(); // timer starts
			}
			break;
		}
	}
else if (effect->duration_type == PER_TICK)// we have to put manually every NEW EFFECT that has a TIMER (and create the timer in entity.h or in this case Player.h)
	{
		switch (effect->attribute_to_change)
		{
		case HEALTH:
			if (effect->name == effects[POISON].name)
			{
				if (entity->poison_tick_active == false)
				{
					entity->poison_tick_active = true;
				}
				entity->poison_tick.Start(); // start or restart timer
				entity->poison_tick_iterator = 0; //restart iterator
			}
			break;
```

To finish with this section, I'm going to introduce two more functions that are used in *Update*, these are ***RestartAttribute()*** and ***ApplyEachTick()***. The first is only used for *TEMPORARY* effects while the second is only used for *PER_TICK* effects.

*RestartAttribute(effect, entity)* compares the timer with the *duration_value* of the effect, and when the timer is bigger, the attribute value of the entity is restarted using the *og_attribute* value. ***This function also has to be updated whenever a new PERMANENT effect is added***.

*ApplyEachTick(effect, entity)* is in charge of calling the *DoMath()* function every tick (notice on the code above that when we apply a *PER_TICK* effect the *DoMath()* function is not called). ***This function also has to be updated whenever a new PER_TICK effect is added***.


# TODOs

**OBJECTIVE:**
You have to create a new effect called ***Ghost*** which has to be a *TEMPORARY BUFF*. When ***Ghost*** is applied (clicking button 1) the player' *SPEED* should increase +10 lasting 3 seconds. Good luck!

Download the release to see the final result [HERE](https://github.com/JosepLleal/Research_Buff_Manager/releases/download/1.0/BuffManager_Solution.zip).

[CLICK HERE](https://github.com/JosepLleal/Research_Buff_Manager/archive/master.zip) to download my repository, inside the folder *Exercise* open the *Handout* to start the doing TODOs.

**TODO 0:**

Create the effect with all his correct properties.

<details> 
  <summary>Click to see TODO 0 solution </summary>
  <p> 
	<img src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/TODO0.png" />
  </p>
</details>



**TODO 1:**

<details> 
  <summary>Click to see TODO 1 solution </summary>
  <p> 
	<img src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/TODO1.png" />
  </p>
</details>



**TODO 2:**

<details> 
  <summary>Click to see TODO 2 solution </summary>
  <p> 
	<img src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/TODO2.png" />
  </p>
</details>



**TODO 3:**

<details> 
  <summary>Click to see TODO 3 solution </summary>
  <p> 
	<img src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/TODO3.png" />
  </p>
</details>



**TODO 4:**

<details> 
  <summary>Click to see TODO 4 solution </summary>
  <p> 
	<img src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/TODO4.png" />
  </p>
</details>



**TODO 5:**

<details> 
  <summary>Click to see TODO 5 solution </summary>
  <p> 
	<img src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/TODO5.png" />
  </p>
</details>



**TODO 6:**

<details> 
  <summary>Click to see TODO 6 solution </summary>
  <p> 
	<img src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/TODO6.png" />
  </p>
</details>



**TODO 7:**

<details> 
  <summary>Click to see TODO 7 solution </summary>
  <p> 
	<img src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/TODO7.png" />
  </p>
</details>




