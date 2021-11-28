#include "Material.h"



Material::Material()
{
	ambientIntensity = 0.0f;
	ambientColour = glm::vec4(0.0f);

	ambientIntensity = 0.0f;
	ambientColour = glm::vec4(0.0f);

	ambientIntensity = 0.0f;
	ambientColour = glm::vec4(0.0f);

	shininess = 0.0f;
}

Material::Material(GLfloat aIntensity, GLfloat dIntensity, GLfloat sIntensity, int materialType, int* currTexture)
{
	ambientIntensity = aIntensity;
	diffuseIntensity = dIntensity;
	specularIntensity = sIntensity;

	setMaterial(materialType, currTexture);
}

void Material::UseMaterial(GLuint ambientIntensityLocation, GLuint diffuseIntensityLocation, GLuint specularIntensityLocation, GLuint shininessLocation,
	GLuint ambientColourLocation, GLuint diffuseColourLocation, GLuint specularColourLocation)
{
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform4f(ambientColourLocation, ambientColour[0], ambientColour[1], ambientColour[2], ambientColour[3]);

	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
	glUniform4f(diffuseColourLocation, diffuseColour[0], diffuseColour[1], diffuseColour[2], diffuseColour[3]);

	glUniform1f(specularIntensityLocation, specularIntensity);
	glUniform4f(specularColourLocation, specularColour[0], specularColour[1], specularColour[2], specularColour[3]);

	glUniform1f(shininessLocation, shininess);
}

void Material::updateMaterial(GLfloat aIntensity, GLfloat dIntensity, GLfloat sIntensity)
{
	ambientIntensity = aIntensity;
	diffuseIntensity = dIntensity;
	specularIntensity = sIntensity;
}

void Material::setMaterial(int materialType, int* currentTexture)
{
	switch (materialType) {
	case brass:
		setBrass();
		*currentTexture = brass;
		break;
	case bronze:
		setBronze();
		*currentTexture = bronze;
		break;
	case polishedBronze:
		setPolishedBronze();
		*currentTexture = polishedBronze;
		break;
	case chrome:
		setChrome();
		*currentTexture = chrome;
		break;
	case copper:
		setCopper();
		*currentTexture = copper;
		break;
	case polishedCopper:
		setPolishedCopper();
		*currentTexture = polishedCopper;
		break;
	case gold:
		setGold();
		*currentTexture = gold;
		break;
	case polishedGold:
		setPolishedGold();
		*currentTexture = polishedGold;
		break;
	case pewter:
		setPewter();
		*currentTexture = pewter;
		break;
	case silver:
		setSilver();
		*currentTexture = silver;
		break;
	case polishedSilver:
		setPolishedSilver();
		*currentTexture = polishedSilver;
		break;
	case emerald:
		setEmerald();
		*currentTexture = emerald;
		break;
	case jade:
		setJade();
		*currentTexture = jade;
		break;
	case obsidian:
		setObsidian();
		*currentTexture = obsidian;
		break;
	case pearl:
		setPearl();
		*currentTexture = pearl;
		break;
	case ruby:
		setRuby();
		*currentTexture = ruby;
		break;
	case turquoise:
		setTurquoise();
		*currentTexture = turquoise;
		break;
	case blackPlastic:
		setBlackPlastic();
		*currentTexture = blackPlastic;
		break;
	case blackRubber:
		setBlackRubber();
		*currentTexture = blackRubber;
		break;
	case plain:
		setPlain();
		*currentTexture = plain;
	}
	//printMaterialInfo();
}

const char** Material::getMaterials()
{
	return materialNames;
}

void Material::printMaterialInfo()
{
	printf("\nambient col: R - %f G - %f B - %f", ambientColour.x, ambientColour.y, ambientColour.z);
	printf("\ndiff col: R - %f G - %f B - %f", diffuseColour.x, diffuseColour.y, diffuseColour.z);
	printf("\nspec col: R - %f G - %f B - %f\n", specularColour.x, specularColour.y, specularColour.z);
}

void Material::setBrass()
{
	ambientColour = glm::vec4(BrassAmbient[0], BrassAmbient[1], BrassAmbient[2], BrassAmbient[3]);
	diffuseColour = glm::vec4(BrassDiffuse[0], BrassDiffuse[1], BrassDiffuse[2], BrassDiffuse[3]);
	specularColour = glm::vec4(BrassSpecular[0], BrassSpecular[1], BrassSpecular[2], BrassSpecular[3]);
	shininess = BrassShininess;
}

void Material::setBronze()
{
	ambientColour = glm::vec4(BronzeAmbient[0], BronzeAmbient[1], BronzeAmbient[2], BronzeAmbient[3]);
	diffuseColour = glm::vec4(BronzeDiffuse[0], BronzeDiffuse[1], BronzeDiffuse[2], BronzeDiffuse[3]);
	specularColour = glm::vec4(BronzeSpecular[0], BronzeSpecular[1], BronzeSpecular[2], BronzeSpecular[3]);
	shininess = BronzeShininess;
}

void Material::setPolishedBronze()
{
	ambientColour = glm::vec4(PolishedBronzeAmbient[0], PolishedBronzeAmbient[1], PolishedBronzeAmbient[2], PolishedBronzeAmbient[3]);
	diffuseColour = glm::vec4(PolishedBronzeDiffuse[0], PolishedBronzeDiffuse[1], PolishedBronzeDiffuse[2], PolishedBronzeDiffuse[3]);
	specularColour = glm::vec4(PolishedBronzeSpecular[0], PolishedBronzeSpecular[1], PolishedBronzeSpecular[2], PolishedBronzeSpecular[3]);
	shininess = PolishedBronzeShininess;
}

void Material::setChrome()
{
	ambientColour = glm::vec4(ChromeAmbient[0], ChromeAmbient[1], ChromeAmbient[2], ChromeAmbient[3]);
	diffuseColour = glm::vec4(ChromeDiffuse[0], ChromeDiffuse[1], ChromeDiffuse[2], ChromeDiffuse[3]);
	specularColour = glm::vec4(ChromeSpecular[0], ChromeSpecular[1], ChromeSpecular[2], ChromeSpecular[3]);
	shininess = ChromeShininess;
}

void Material::setCopper()
{
	ambientColour = glm::vec4(CopperAmbient[0], CopperAmbient[1], CopperAmbient[2], CopperAmbient[3]);
	diffuseColour = glm::vec4(CopperDiffuse[0], CopperDiffuse[1], CopperDiffuse[2], CopperDiffuse[3]);
	specularColour = glm::vec4(CopperSpecular[0], CopperSpecular[1], CopperSpecular[2], CopperSpecular[3]);
	shininess = CopperShininess;
}

void Material::setPolishedCopper()
{
	ambientColour = glm::vec4(PolishedCopperAmbient[0], PolishedCopperAmbient[1], PolishedCopperAmbient[2], PolishedCopperAmbient[3]);
	diffuseColour = glm::vec4(PolishedCopperDiffuse[0], PolishedCopperDiffuse[1], PolishedCopperDiffuse[2], PolishedCopperDiffuse[3]);
	specularColour = glm::vec4(PolishedCopperSpecular[0], PolishedCopperSpecular[1], PolishedCopperSpecular[2], PolishedCopperSpecular[3]);
	shininess = PolishedCopperShininess;
}

void Material::setGold()
{
	ambientColour = glm::vec4(GoldAmbient[0], GoldAmbient[1], GoldAmbient[2], GoldAmbient[3]);
	diffuseColour = glm::vec4(GoldDiffuse[0], GoldDiffuse[1], GoldDiffuse[2], GoldDiffuse[3]);
	specularColour = glm::vec4(GoldSpecular[0], GoldSpecular[1], GoldSpecular[2], GoldSpecular[3]);
	shininess = GoldShininess;
}

void Material::setPolishedGold()
{
	ambientColour = glm::vec4(PolishedGoldAmbient[0], PolishedGoldAmbient[1], PolishedGoldAmbient[2], PolishedGoldAmbient[3]);
	diffuseColour = glm::vec4(PolishedGoldDiffuse[0], PolishedGoldDiffuse[1], PolishedGoldDiffuse[2], PolishedGoldDiffuse[3]);
	specularColour = glm::vec4(PolishedGoldSpecular[0], PolishedGoldSpecular[1], PolishedGoldSpecular[2], PolishedGoldSpecular[3]);
	shininess = PolishedGoldShininess;
}

void Material::setPewter()
{
	ambientColour = glm::vec4(PewterAmbient[0], PewterAmbient[1], PewterAmbient[2], PewterAmbient[3]);
	diffuseColour = glm::vec4(PewterDiffuse[0], PewterDiffuse[1], PewterDiffuse[2], PewterDiffuse[3]);
	specularColour = glm::vec4(PewterSpecular[0], PewterSpecular[1], PewterSpecular[2], PewterSpecular[3]);
	shininess = PewterShininess;
}

void Material::setSilver()
{
	ambientColour = glm::vec4(SilverAmbient[0], SilverAmbient[1], SilverAmbient[2], SilverAmbient[3]);
	diffuseColour = glm::vec4(SilverDiffuse[0], SilverDiffuse[1], SilverDiffuse[2], SilverDiffuse[3]);
	specularColour = glm::vec4(SilverSpecular[0], SilverSpecular[1], SilverSpecular[2], SilverSpecular[3]);
	shininess = SilverShininess;
}

void Material::setPolishedSilver()
{
	ambientColour = glm::vec4(PolishedSilverAmbient[0], PolishedSilverAmbient[1], PolishedSilverAmbient[2], PolishedSilverAmbient[3]);
	diffuseColour = glm::vec4(PolishedSilverDiffuse[0], PolishedSilverDiffuse[1], PolishedSilverDiffuse[2], PolishedSilverDiffuse[3]);
	specularColour = glm::vec4(PolishedSilverSpecular[0], PolishedSilverSpecular[1], PolishedSilverSpecular[2], PolishedSilverSpecular[3]);
	shininess = PolishedSilverShininess;
}

void Material::setEmerald()
{
	ambientColour = glm::vec4(EmeraldAmbient[0], EmeraldAmbient[1], EmeraldAmbient[2], EmeraldAmbient[3]);
	diffuseColour = glm::vec4(EmeraldDiffuse[0], EmeraldDiffuse[1], EmeraldDiffuse[2], EmeraldDiffuse[3]);
	specularColour = glm::vec4(EmeraldSpecular[0], EmeraldSpecular[1], EmeraldSpecular[2], EmeraldSpecular[3]);
	shininess = EmeraldShininess;
}

void Material::setJade()
{
	ambientColour = glm::vec4(JadeAmbient[0], JadeAmbient[1], JadeAmbient[2], JadeAmbient[3]);
	diffuseColour = glm::vec4(JadeDiffuse[0], JadeDiffuse[1], JadeDiffuse[2], JadeDiffuse[3]);
	specularColour = glm::vec4(JadeSpecular[0], JadeSpecular[1], JadeSpecular[2], JadeSpecular[3]);
	shininess = JadeShininess;
}

void Material::setObsidian()
{
	ambientColour = glm::vec4(ObsidianAmbient[0], ObsidianAmbient[1], ObsidianAmbient[2], ObsidianAmbient[3]);
	diffuseColour = glm::vec4(ObsidianDiffuse[0], ObsidianDiffuse[1], ObsidianDiffuse[2], ObsidianDiffuse[3]);
	specularColour = glm::vec4(ObsidianSpecular[0], ObsidianSpecular[1], ObsidianSpecular[2], ObsidianSpecular[3]);
	shininess = ObsidianShininess;
}

void Material::setPearl()
{
	ambientColour = glm::vec4(PearlAmbient[0], PearlAmbient[1], PearlAmbient[2], PearlAmbient[3]);
	diffuseColour = glm::vec4(PearlDiffuse[0], PearlDiffuse[1], PearlDiffuse[2], PearlDiffuse[3]);
	specularColour = glm::vec4(PearlSpecular[0], PearlSpecular[1], PearlSpecular[2], PearlSpecular[3]);
	shininess = PearlShininess;
}

void Material::setRuby()
{
	ambientColour = glm::vec4(RubyAmbient[0], RubyAmbient[1], RubyAmbient[2], RubyAmbient[3]);
	diffuseColour = glm::vec4(RubyDiffuse[0], RubyDiffuse[1], RubyDiffuse[2], RubyDiffuse[3]);
	specularColour = glm::vec4(RubySpecular[0], RubySpecular[1], RubySpecular[2], RubySpecular[3]);
	shininess = RubyShininess;
}

void Material::setTurquoise()
{
	ambientColour = glm::vec4(TurquoiseAmbient[0], TurquoiseAmbient[1], TurquoiseAmbient[2], TurquoiseAmbient[3]);
	diffuseColour = glm::vec4(TurquoiseDiffuse[0], TurquoiseDiffuse[1], TurquoiseDiffuse[2], TurquoiseDiffuse[3]);
	specularColour = glm::vec4(TurquoiseSpecular[0], TurquoiseSpecular[1], TurquoiseSpecular[2], TurquoiseSpecular[3]);
	shininess = TurquoiseShininess;
}

void Material::setBlackPlastic()
{
	ambientColour = glm::vec4(BlackPlasticAmbient[0], BlackPlasticAmbient[1], BlackPlasticAmbient[2], BlackPlasticAmbient[3]);
	diffuseColour = glm::vec4(BlackPlasticDiffuse[0], BlackPlasticDiffuse[1], BlackPlasticDiffuse[2], BlackPlasticDiffuse[3]);
	specularColour = glm::vec4(BlackPlasticSpecular[0], BlackPlasticSpecular[1], BlackPlasticSpecular[2], BlackPlasticSpecular[3]);
	shininess = BlackPlasticShininess;
}

void Material::setBlackRubber()
{
	ambientColour = glm::vec4(BlackRubberAmbient[0], BlackRubberAmbient[1], BlackRubberAmbient[2], BlackRubberAmbient[3]);
	diffuseColour = glm::vec4(BlackRubberDiffuse[0], BlackRubberDiffuse[1], BlackRubberDiffuse[2], BlackRubberDiffuse[3]);
	specularColour = glm::vec4(BlackRubberSpecular[0], BlackRubberSpecular[1], BlackRubberSpecular[2], BlackRubberSpecular[3]);
	shininess = BlackRubberShininess;
}

void Material::setPlain()
{
	ambientColour = glm::vec4(PlainAmbient[0], PlainAmbient[1], PlainAmbient[2], PlainAmbient[3]);
	diffuseColour = glm::vec4(PlainDiffuse[0], PlainDiffuse[1], PlainDiffuse[2], PlainDiffuse[3]);
	specularColour = glm::vec4(PlainSpecular[0], PlainSpecular[1], PlainSpecular[2], PlainSpecular[3]);
	shininess = PlainShininess;
}

Material::~Material()
{
}
