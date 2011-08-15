/*
 * GrandOrgue - free pipe organ simulator based on MyOrgan
 *
 * MyOrgan 1.0.6 Codebase - Copyright 2006 Milan Digital Audio LLC
 * MyOrgan is a Trademark of Milan Digital Audio LLC
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#include "GOrgueDivisionalCoupler.h"
#include "GrandOrgueFile.h"

/* TODO: This should not be... */
extern GrandOrgueFile* organfile;

GOrgueDivisionalCoupler::GOrgueDivisionalCoupler() :
	GOrgueDrawstop(),
	m_BiDirectionalCoupling(false),
	m_manuals(0)
{
}


void GOrgueDivisionalCoupler::Load(IniFileConfig& cfg, wxString group, int firstValidManualIndex, int numberOfManuals, GOrgueDisplayMetrics* displayMetrics)
{
	wxString buffer;

	m_BiDirectionalCoupling=cfg.ReadBoolean( group,wxT("BiDirectionalCoupling"));
	unsigned NumberOfManuals=cfg.ReadInteger( group,wxT("NumberOfManuals"),  1, numberOfManuals - firstValidManualIndex + 1);

	m_manuals.resize(0);
	for (unsigned i = 0; i < NumberOfManuals; i++)
	{
		buffer.Printf(wxT("Manual%03d"), i + 1);
		m_manuals.push_back(cfg.ReadInteger(group, buffer, firstValidManualIndex, numberOfManuals));
	}
	GOrgueDrawstop::Load(cfg, group, displayMetrics);

}

void GOrgueDivisionalCoupler::Save(IniFileConfig& cfg, bool prefix, wxString group)
{
	GOrgueDrawstop::Save(cfg, prefix, group);
}

void GOrgueDivisionalCoupler::Set(bool on)
{

	if (DefaultToEngaged == on)
		return;
	GOrgueDrawstop::Set(on);

}

unsigned GOrgueDivisionalCoupler::GetNumberOfManuals()
{
	return m_manuals.size();
}

unsigned GOrgueDivisionalCoupler::GetManual(unsigned index)
{
	return m_manuals[index];
}

bool GOrgueDivisionalCoupler::IsBidirectional()
{
	return m_BiDirectionalCoupling;
}
