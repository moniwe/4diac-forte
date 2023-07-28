/*********************************************************************
 * Copyright (c) 2022 Davor Cihlar
 *
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 *
 * SPDX-License-Identifier: EPL-2.0
 *
 * Contributors:
 *   Davor Cihlar
 *     - initial implementation
 **********************************************************************/

#ifndef _IF_SPEC_BUILDER_H_
#define _IF_SPEC_BUILDER_H_

#include <vector>
#include <array>
#include <tuple>
#include <funcbloc.h>


namespace forte::core::util {

class CMixedStorage;

class CInputSpecTag;    ///< helper class for distinguishing inputs from outputs (not an actual class)
class COutputSpecTag;   ///< helper class for distinguishing outputs from intputs (not an actual class)
class CDataSpecTag;     ///< helper class for distinguishing data from events (not an actual class)
class CEventSpecTag;    ///< helper class for distinguishing events from data (not an actual class)


/**
 * @brief Reference to a port within CIfSpecBuilder.
 *
 * This is usually returned when adding a port.
 *
 * @tparam TypeTag port type (data or event, CDataSpecTag or CEventSpecTag)
 * @tparam DirTag port direction (input or output, CInputSpecTag or COutputSpecTag)
 */
template<class TypeTag, class DirTag>
class CSpecReference {
  public:
    constexpr CSpecReference() = default;
    constexpr CSpecReference(int paRef) {
      if (paRef < 0) {
        mRef = scmMaxRefValue;
      } else {
        mRef = static_cast<TDataIOID>(paRef);
      }
    }

    /**
     * @brief Checks if reference is valid
     * @return true if valid
     */
    constexpr bool isValid() const {
      return mRef != scmMaxRefValue;
    }

    /**
     * @brief Dereferences the reference (converts to index as integer)
     * @return port index
     */
    constexpr auto operator*() const {
      return mRef;
    }

  private:
    static constexpr auto scmMaxRefValue = std::numeric_limits<TDataIOID>::max();

    TDataIOID mRef = scmMaxRefValue;
};

/**
 * @brief Reference to a port range within CIfSpecBuilder.
 *
 * This is usually returned when adding a port range.
 * The range can not be empty.
 *
 * @tparam TypeTag port type (data or event, CDataSpecTag or CEventSpecTag)
 * @tparam DirTag port direction (input or output, CInputSpecTag or COutputSpecTag)
 */
template<class TypeTag, class DirTag>
class CSpecReferenceRange {
  public:
    using TCSpecReference = CSpecReference<TypeTag, DirTag>;

    TCSpecReference mFirst;   ///< first port reference
    TCSpecReference mLast;    ///< last port reference

    constexpr CSpecReferenceRange() = default;
    constexpr CSpecReferenceRange(TCSpecReference paFirst, TCSpecReference paLast)
      : mFirst(paFirst), mLast(paLast)
    {}
    constexpr CSpecReferenceRange(std::pair<int, int> paRangePair)
      : CSpecReferenceRange(std::get<0>(paRangePair), std::get<1>(paRangePair))
    {}

    /**
     * @brief Access one port from within the range.
     * @param offset offset within the range
     * @return reference to one port
     */
    constexpr TCSpecReference operator[](int paOffset) const {
      int id = *mFirst + paOffset;
      return { isValid() && id >= *mFirst && id <= *mLast ? id : -1 };
    }

    /**
     * @brief Checks if range is valid
     * @return true if valid
     */
    constexpr bool isValid() const {
      return mFirst.isValid() && mLast.isValid();
    }
};

/**
 * @brief Common string list handler for CDataSpecBuilder and CEventSpecBuilder.
 *
 * It supports both static and dynamic allocation.
 */
class CStringIdListSpecBuilder {
  public:
    CStringIdListSpecBuilder(std::size_t paMaxItems) : cmMaxItems(paMaxItems)
    {}

    /**
     * @brief Sets list to the statically allocated one.
     * @param paStaticList statically allocated list
     * @param paItemsCount number of items in the list
     */
    void setStaticList(const CStringDictionary::TStringId *paStaticList, std::size_t paItemsCount);

    /**
     * @brief Add string from dictionary to list.
     * @param paStringId string ID to add
     * @return index of the added string
     */
    int addString(const CStringDictionary::TStringId paStringId);
    /**
     * @brief Add C string to list.
     *
     * The string will be first added to CStringDictionary.
     *
     * @param paString C string to add
     * @return index of the added string
     */
    int addString(const char *paString);

    /**
     * @brief Returns the number of added strings.
     * @return number of added strings
     */
    std::size_t getNumStrings() const {
      return cmStaticList ? mStaticListSize : mDynamicList.size();
    }

    /**
     * @brief Refurns index of the specified C string.
     * @param paString string to find
     * @return index of the specified string
     */
    int findString(const char *paString) const;
    /**
     * @brief Refurns index of the specified dictionary string ID.
     * @param paStringId string ID to find
     * @return index of the specified string
     */
    int findString(CStringDictionary::TStringId paStringId) const;

    /**
     * @brief Calculates required dynamic data size.
     * @return required dynamic data size
     */
    std::size_t calcStorageSize() const;
    std::tuple<const CStringDictionary::TStringId*, TForteUInt8> build(CMixedStorage &paStorage) const;

    /**
     * @brief Checks configuration status.
     * @return true if everything's ok
     */
    bool isGood() const { return getNumStrings() <= cmMaxItems; }

  private:
    const std::size_t cmMaxItems;
    std::vector<CStringDictionary::TStringId> mDynamicList;
    std::size_t mStaticListSize = 0;
    const CStringDictionary::TStringId *cmStaticList = nullptr;
};

/**
 * @brief Base helper for CIfSpecBuilder managing events.
 */
class CEventSpecBuilderBase {
  public:
    /**
     * @brief Set statically defined configuration.
     * @param pa_aunStaticNames see SFBInterfaceSpec.m_aunEINames / SFBInterfaceSpec.m_aunEONames
     * @param pa_nEventsCount see SFBInterfaceSpec.m_nNumEIs / SFBInterfaceSpec.m_nNumEOs
     */
    void setStaticEvents(const CStringDictionary::TStringId *pa_aunStaticNames, std::size_t pa_nEventsCount) {
      m_oNamesListBuilder.setStaticList(pa_aunStaticNames, pa_nEventsCount);
    }
    /**
     * @brief Sets statically defined configuration through std::array.
     * @tparam N see SFBInterfaceSpec.m_nNumEIs / SFBInterfaceSpec.m_nNumEOs; should be automatically deduced
     * @param pa_aunStaticNames see SFBInterfaceSpec.m_aunEINames / SFBInterfaceSpec.m_aunEONames
     */
    template<std::size_t N>
    void setStaticEvents(const std::array<CStringDictionary::TStringId, N> &pa_aStaticNames) {
      setStaticEvents(pa_aStaticNames.data(), pa_aStaticNames.size());
    }

    /**
     * @brief Gets number of added events.
     * @return number of added events
     */
    auto getNumEvents() const {
      return m_oNamesListBuilder.getNumStrings();
    }

    /**
     * @brief Finds port index from event port name.
     * @param pa_tName port name
     * @return port index or -1 if not found
     */
    template<typename T>
    int findEvent(T pa_tName) const {
      return m_oNamesListBuilder.findString(pa_tName);
    }

    /**
     * @brief Calculates required dynamic data size.
     * @return required dynamic data size
     */
    auto calcStorageSize() const {
      return m_oNamesListBuilder.calcStorageSize();
    }
    auto build(CMixedStorage &pa_oStorage) const {
      return m_oNamesListBuilder.build(pa_oStorage);
    }

    /**
     * @brief Checks configuration status.
     * @return true if everything's ok
     */
    bool isGood() const {
      return m_oNamesListBuilder.isGood() && m_bIsGood;
    }

  private:
    static constexpr auto scm_unMaxEvents = CFunctionBlock::scm_nMaxInterfaceEvents;
    bool m_bIsGood = true;
    CStringIdListSpecBuilder m_oNamesListBuilder{scm_unMaxEvents};

  protected:
    template<typename NameType>
    int addEvent(NameType pa_xName) {
      return m_oNamesListBuilder.addString(pa_xName);
    }

    std::pair<int, int> addEventRange(const char *pa_sPrefix, int pa_nRangeSize);
};

/**
 * @brief Helper for CIfSpecBuilder managing events with direction dependency.
 *
 * Template is used to make input and output events incompatible.
 *
 * @tparam DirTag defines input or output events
 */
template<class DirTag>
class CEventSpecBuilder : public CEventSpecBuilderBase {
  public:
    using TCSpecReference = CSpecReference<CEventSpecTag, DirTag>;
    using TCSpecReferenceRange = CSpecReferenceRange<CEventSpecTag, DirTag>;

    /**
     * @brief Adds event port.
     * @param pa_xName port name
     * @return reference to the added port
     */
    template<typename TNameType>
    TCSpecReference addEvent(TNameType pa_xName) {
      return CEventSpecBuilderBase::addEvent(pa_xName);
    }

    /**
     * @brief Adds a range of numerated event ports with the same name prefix.
     * @param pa_sPrefix name prefix
     * @param pa_nRangeSize number of event ports in range
     * @return reference to the whole range added
     */
    TCSpecReferenceRange addEventRange(const char *pa_sPrefix, int pa_nRangeSize) {
      return CEventSpecBuilderBase::addEventRange(pa_sPrefix, pa_nRangeSize);
    }

    /**
     * @brief Access reference of a given port.
     * @return reference
     */
    template<typename TNameType>
    TCSpecReference operator[] (TNameType pa_tName) const {
      return { findEvent(pa_tName) };
    }
};

/**
 * @brief Base helper for CIfSpecBuilder managing data.
 */
class CDataSpecBuilderBase {
  public:
    /**
     * @brief Sets statically defined configuration.
     * @param pa_aunStaticDataNames see SFBInterfaceSpec.m_aunDINames / SFBInterfaceSpec.m_aunDONames
     * @param pa_aunStaticTypeNames see SFBInterfaceSpec.m_aunDIDataTypeNames / SFBInterfaceSpec.m_aunDODataTypeNames
     * @param pa_nDataCount see SFBInterfaceSpec.m_nNumDIs / SFBInterfaceSpec.m_nNumDOs
     */
    void setStaticData(const CStringDictionary::TStringId *pa_aunStaticDataNames, const CStringDictionary::TStringId *pa_aunStaticTypeNames, std::size_t pa_nDataCount) {
      m_oNamesListBuilder.setStaticList(pa_aunStaticDataNames, pa_nDataCount);
      m_oTypesListBuilder.setStaticList(pa_aunStaticTypeNames, pa_nDataCount);
    }
    /**
     * @brief Sets statically defined configuration through std::array.
     * @tparam N see SFBInterfaceSpec.m_nNumDIs / SFBInterfaceSpec.m_nNumDOs; should be automatically deduced
     * @param pa_aunStaticDataNames see SFBInterfaceSpec.m_aunDINames / SFBInterfaceSpec.m_aunDONames
     * @param pa_aunStaticTypeNames see SFBInterfaceSpec.m_aunDIDataTypeNames / SFBInterfaceSpec.m_aunDODataTypeNames
     */
    template<std::size_t N>
    void setStaticData(const std::array<CStringDictionary::TStringId, N> &pa_aunStaticDataNames, const std::array<CStringDictionary::TStringId, N> &pa_aunStaticTypeNames) {
      setStaticData(pa_aunStaticDataNames.data(), pa_aunStaticTypeNames.data(), N);
    }

    /**
     * @brief Finds port index from data port name.
     * @param pa_tName port name
     * @return port index or -1 if not found
     */
    template<typename T>
    int findData(T pa_tName) const {
      return m_oNamesListBuilder.findString(pa_tName);
    }

    /**
     * @brief Calculates required dynamic data size.
     * @return required dynamic data size
     */
    std::size_t calcStorageSize() const {
      return m_oNamesListBuilder.calcStorageSize() + m_oTypesListBuilder.calcStorageSize();
    }
    std::tuple<const CStringDictionary::TStringId*, const CStringDictionary::TStringId*, TForteUInt8> build(CMixedStorage &pa_oStorage) const;

    /**
     * @brief Checks configuration status.
     * @return true if everything's ok
     */
    bool isGood() const {
      return m_oNamesListBuilder.isGood() && m_oTypesListBuilder.isGood() && m_bIsGood;
    }

  private:
    static constexpr auto scm_unMaxData = CFunctionBlock::scm_nMaxInterfaceEvents;
    bool m_bIsGood = true;
    CStringIdListSpecBuilder m_oNamesListBuilder{scm_unMaxData};
    CStringIdListSpecBuilder m_oTypesListBuilder{scm_unMaxData};

  protected:
    template<typename TNameType1, typename TNameType2>
    int addData(TNameType1 pa_xName, TNameType2 pa_xTypeName) {
      m_oNamesListBuilder.addString(pa_xName);
      return m_oTypesListBuilder.addString(pa_xTypeName);
    }
    std::pair<int, int> addDataRange(const char *pa_sPrefix, int pa_nRangeSize);
    std::pair<int, int> addDataRange(const char *pa_sPrefix, int pa_nRangeSize, CStringDictionary::TStringId pa_unTypeName);
    std::pair<int, int> addDataRange(const char *pa_sPrefix, int pa_nRangeSize, const char *pa_sTypeName);
};

/**
 * @brief Helper for CIfSpecBuilder managing data with direction dependency.
 *
 * Template is used to make input and output data incompatible.
 *
 * @tparam DirTag defines input or output data
 */
template<class DirTag>
class CDataSpecBuilder : public CDataSpecBuilderBase {
  public:
    using TCSpecReference = CSpecReference<CDataSpecTag, DirTag>;
    using TCSpecReferenceRange = CSpecReferenceRange<CDataSpecTag, DirTag>;

    /**
     * @brief Adds data port.
     * @param pa_xName port name
     * @param pa_xTypeName port data type name
     * @return reference to the added port
     */
    template<typename TNameType1, typename TNameType2>
    TCSpecReference addData(TNameType1 pa_xName, TNameType2 pa_xTypeName) {
      return CDataSpecBuilderBase::addData(pa_xName, pa_xTypeName);
    }

    /**
     * @brief Adds a range of numerated data ports with the same name prefix and of ANY type.
     * @param pa_sPrefix name prefix
     * @param pa_nRangeSize number of data ports in range
     * @return reference to the whole range added
     */
    TCSpecReferenceRange addDataRange(const char *pa_sPrefix, int pa_nRangeSize) {
      return CDataSpecBuilderBase::addDataRange(pa_sPrefix, pa_nRangeSize);
    }
    /**
     * @brief Adds a range of numerated data ports with the same name prefix.
     * @param pa_sPrefix name prefix
     * @param pa_nRangeSize number of data ports in range
     * @param pa_xTypeName data type name for every port
     * @return reference to the whole range added
     */
    template<typename TNameType>
    TCSpecReferenceRange addDataRange(const char *pa_sPrefix, int pa_nRangeSize, TNameType pa_xTypeName) {
      return CDataSpecBuilderBase::addDataRange(pa_sPrefix, pa_nRangeSize, pa_xTypeName);
    }

    /**
     * @brief Access reference of a given port.
     * @return reference
     */
    template<typename TNameType>
    TCSpecReference operator[] (TNameType pa_tName) const {
      return { findData(pa_tName) };
    }
};

/**
 * @brief Base helper for CIfSpecBuilder managing bindings (withs).
 *
 * This base class is unaware of data and event directions so
 * it's not recommended to be used directly.
 */
class CWithSpecBuilderBase {
  public:
    /**
     * @brief Sets statically defined configuration.
     * @param pa_aunStaticBindings see SFBInterfaceSpec.m_anEIWith / SFBInterfaceSpec.m_anEOWith
     * @param pa_anStaticIndexes see SFBInterfaceSpec.m_anEIWithIndexes / SFBInterfaceSpec.m_anEOWithIndexes
     * @param pa_unNumEvents see SFBInterfaceSpec.m_nNumEIs / SFBInterfaceSpec.m_nNumEOs
     */
    void setStaticBindings(const TDataIOID *pa_aunStaticBindings, const TForteInt16 *pa_anStaticIndexes, std::size_t pa_unNumEvents);
    /**
     * @brief Sets statically defined configuration through std::array.
     * @tparam NBindings number of bindings; should be automatically deduced
     * @tparam NEvents see SFBInterfaceSpec.m_nNumEIs / SFBInterfaceSpec.m_nNumEOs; should be automatically deduced
     * @param pa_aunStaticBindings see SFBInterfaceSpec.m_anEIWith / SFBInterfaceSpec.m_anEOWith
     * @param pa_anStaticIndexes see SFBInterfaceSpec.m_anEIWithIndexes / SFBInterfaceSpec.m_anEOWithIndexes
     */
    template<std::size_t NBindings, std::size_t NEvents>
    void setStaticBindings(const std::array<TDataIOID, NBindings> &pa_aunStaticBindings, const std::array<TForteInt16, NEvents> &pa_anStaticIndexes) {
      setStaticBindings(pa_aunStaticBindings.data(), pa_anStaticIndexes.data(), NEvents);
    }

    /**
     * @brief Binds data to event.
     * @param pa_unEventId event port id
     * @param pa_unDataId data port id
     */
    void bind(TDataIOID pa_unEventId, TDataIOID pa_unDataId);
    /**
     * @brief Binds multiple data to a single event.
     * @param pa_unEventId event port id
     * @param pa_unDataId a list of data port ids
     */
    void bind(TDataIOID pa_unEventId, std::initializer_list<TDataIOID> pa_aunDataIds) {
      for (auto dataId : pa_aunDataIds) {
        bind(pa_unEventId, dataId);
      }
    }
    /**
     * @brief Binds a range of data ports to an event.
     * @param pa_unEventId event port id
     * @param pa_unFirstDataId first data port id
     * @param pa_unLastDataId last data port id
     */
    void bindRange(TDataIOID pa_unEventId, TDataIOID pa_unFirstDataId, TDataIOID pa_unLastDataId);

    /**
     * @brief Calculates required dynamic data size.
     * @param pa_unNumEvents number of events in the FB
     * @return required dynamic data size
     */
    std::size_t calcStorageSize(std::size_t pa_unNumEvents) const;
    std::tuple<const TDataIOID*, const TForteInt16*> build(CMixedStorage &pa_oStorage, std::size_t pa_unNumEvents);

    /**
     * @brief Checks configuration status.
     * @return true if everything's ok
     */
    bool isGood() const { return m_bIsGood; }

  private:
    bool m_bIsGood = true;
    const TDataIOID *m_aunStaticBindings = nullptr;
    const TForteInt16 *m_anStaticIndexes = nullptr;
    std::size_t m_unNumStaticEvents = 0;
    std::vector<std::vector<TDataIOID>> m_vvDynamicList;

    void grow(std::size_t pa_unNumEvents);

  protected:
    bool check(bool pa_bState) {
      m_bIsGood = m_bIsGood && pa_bState;
      return isGood();
    }
};

/**
 * @brief Helper for CIfSpecBuilder managing bindings (withs) with direction dependency.
 *
 * If explicit with specification is not required then simple and automatic binding
 * through CIfSpecBuilder is recommended.
 *
 * Template is used to make input and output withs incompatible.
 *
 * @tparam DirTag defines input or output withs
 */
template<class DirTag>
class CWithSpecBuilder : public CWithSpecBuilderBase {
  public:
    using TCSpecEventReference = CSpecReference<CEventSpecTag, DirTag>;
    using TCSpecDataReference = CSpecReference<CDataSpecTag, DirTag>;
    using TCSpecDataReferenceRange = CSpecReferenceRange<CDataSpecTag, DirTag>;

    /**
     * @brief Add a binding with a single data port.
     * @param pa_oEventRef event to bind to
     * @param pa_oDataRef data
     */
    void bind(TCSpecEventReference pa_oEventRef, TCSpecDataReference pa_oDataRef) {
      if (check(pa_oEventRef.isValid() && pa_oDataRef.isValid())) {
        CWithSpecBuilderBase::bind(*pa_oEventRef, *pa_oDataRef);
      }
    }
    /**
     * @brief Add a binding with multiple data ports.
     * @param pa_oEventRef event to bind to
     * @param pa_aoDataRefs list with data ports
     */
    void bind(TCSpecEventReference pa_oEventRef, std::initializer_list<TCSpecDataReference> pa_aoDataRefs) {
      check(pa_oEventRef.isValid());
      for (auto ref : pa_aoDataRefs) {
        if (!check(ref.isValid()))
            break;
        bind(pa_oEventRef, *ref);
      }
    }

    /**
     * @brief Add bindings to a range of data ports.
     * @param pa_oEventRef event to bind to
     * @param pa_oFirstDataRef first data port
     * @param pa_oLastDataRef last data port
     */
    void bindRange(TCSpecEventReference pa_oEventRef, TCSpecDataReference pa_oFirstDataRef, TCSpecDataReference pa_oLastDataRef) {
      if (check(pa_oEventRef.isValid() && pa_oFirstDataRef.isValid() && pa_oLastDataRef.isValid())) {
        CWithSpecBuilderBase::bindRange(*pa_oEventRef, *pa_oFirstDataRef, *pa_oLastDataRef);
      }
    }
    /**
     * @brief Add bindings to a range of data ports.
     * @param pa_oEventRef event to bind to
     * @param pa_oDataRefRange data port range
     */
    void bindRange(TCSpecEventReference pa_oEventRef, TCSpecDataReferenceRange pa_oDataRefRange) {
      if (check(pa_oEventRef.isValid() && pa_oDataRefRange.isValid())) {
        CWithSpecBuilderBase::bindRange(*pa_oEventRef, *pa_oDataRefRange.mFirst, *pa_oDataRefRange.mLast);
      }
    }
};

/**
 * @brief Helper for CIfSpecBuilder managing adapters.
 */
class CAdapterSpecBuilder {
  public:
    /**
     * @brief Set statically defined configuration.
     * @param pa_aoStaticAdapters see SFBInterfaceSpec.m_pstAdapterInstanceDefinition
     * @param pa_nAdaptersCount see SFBInterfaceSpec.m_nNumAdapters
     */
    void setStaticAdapters(const SAdapterInstanceDef *pa_aoStaticAdapters, std::size_t pa_nAdaptersCount);

    /**
     * @brief Sets statically defined configuration through std::array.
     * @tparam N see SFBInterfaceSpec.m_nNumAdapters
     * @param pa_aoStaticAdapters see SFBInterfaceSpec.m_pstAdapterInstanceDefinition
     */
    template<std::size_t N>
    void setStaticAdapters(const std::array<SAdapterInstanceDef, N> &pa_aoStaticAdapters) {
      setStaticAdapters(pa_aoStaticAdapters.data(), pa_aoStaticAdapters.size());
    }

    /**
     * @brief Adds adapter port (socket/plug).
     * @param pa_unName port name
     * @param pa_unTypeName port type (adapter name)
     * @param pa_bIsPlug true when port is plug (output)
     */
    void addAdapter(const CStringDictionary::TStringId pa_unName, const CStringDictionary::TStringId pa_unType, bool pa_bIsPlug);

    /**
     * @brief Adds adapter port (socket/plug) using C strings.
     *
     * C strings are automatically converted to CStringDictionary.
     *
     * @param pa_sName port name
     * @param pa_sTypeName port type (adapter name)
     * @param pa_bIsPlug true when port is plug (output)
     */
    void addAdapter(const char *pa_sName, const char *pa_sType, bool pa_bIsPlug);

    /**
     * @brief Calculates required dynamic data size.
     * @return required dynamic data size
     */
    std::size_t calcStorageSize() const;
    std::tuple<const SAdapterInstanceDef*, TForteUInt8> build(CMixedStorage &pa_oStorage);

  private:
    std::vector<SAdapterInstanceDef> m_vDynamicList;
    std::size_t m_unStaticAdaptersCount = 0;
    const SAdapterInstanceDef *m_aoStaticAdapters = nullptr;
};

/**
 * @brief Base helper for CAdapterSpecBuilder.
 */
class CAdapterDirHelperBase {
  public:
    /**
     * @brief Adds adapter port (socket/plug).
     * @param pa_xName port name
     * @param pa_xTypeName port type (adapter name)
     * @tparam TNameType string type
     */
    template<typename TNameType>
    void addAdapter(TNameType pa_xName, TNameType pa_xTypeName) {
      m_roBuilder.addAdapter(pa_xName, pa_xTypeName, m_bIsPlug);
    }

  protected:
    constexpr CAdapterDirHelperBase(CAdapterSpecBuilder &pa_roBuilder, bool pa_bIsPlug)
      : m_roBuilder(pa_roBuilder), m_bIsPlug(pa_bIsPlug)
    {}

  private:
    CAdapterSpecBuilder &m_roBuilder;
    bool m_bIsPlug;
};

/**
 * @brief Helper for CAdapterSpecBuilder handling different directions.
 *
 * @tparam DirTag defines input or output adapter
 */
template<class DirTag>
class CAdapterDirHelper;

template<>
class CAdapterDirHelper<CInputSpecTag> : public CAdapterDirHelperBase {
  public:
    constexpr CAdapterDirHelper(CAdapterSpecBuilder &pa_roBuilder)
      : CAdapterDirHelperBase(pa_roBuilder, false)
    {}
};

template<>
class CAdapterDirHelper<COutputSpecTag> : public CAdapterDirHelperBase {
  public:
    constexpr CAdapterDirHelper(CAdapterSpecBuilder &pa_roBuilder)
      : CAdapterDirHelperBase(pa_roBuilder, true)
    {}
};

/**
 * @brief @ref SFBInterfaceSpec structure builder
 *
 * Simplifies filling out @ref SFBInterfaceSpec structure and
 * memory management that goes along with it.
 */
class CIfSpecBuilder {
  public:
    CEventSpecBuilder<CInputSpecTag>  m_oEI;       ///< event inputs
    CEventSpecBuilder<COutputSpecTag> m_oEO;       ///< event outputs
    CDataSpecBuilder<CInputSpecTag>   m_oDI;       ///< data inputs
    CDataSpecBuilder<COutputSpecTag>  m_oDO;       ///< data outputs
    CWithSpecBuilder<CInputSpecTag>   m_oIWith;    ///< input withs
    CWithSpecBuilder<COutputSpecTag>  m_oOWith;    ///< output withs
    CAdapterSpecBuilder               m_oAdapter;  ///< all adapters
    CAdapterDirHelper<CInputSpecTag>  m_oIAdapter{m_oAdapter}; ///< input adapters
    CAdapterDirHelper<COutputSpecTag> m_oOAdapter{m_oAdapter}; ///< output adapters

    /**
     * @brief Binds event to a single data port.
     * @tparam DirTag defines event/data direction; should be automatically deduced
     * @param pa_oEventRef event from #m_oEI or #m_oEO
     * @param pa_oDataRef data from #m_oDI or #m_oDO
     */
    template<class DirTag>
    void bind(CSpecReference<CEventSpecTag, DirTag> pa_oEventRef, CSpecReference<CDataSpecTag, DirTag> pa_oDataRef) {
      getWithFromDir(pa_oEventRef).bind(pa_oEventRef, pa_oDataRef);
    }
    /**
     * @brief Binds event to multiple data ports.
     * @tparam DirTag defines event/data direction; should be automatically deduced
     * @param pa_oEventRef event from #m_oEI or #m_oEO
     * @param pa_loDataRef multiple data from #m_oDI or #m_oDO
     */
    template<class DirTag>
    void bind(CSpecReference<CEventSpecTag, DirTag> pa_oEventRef, std::initializer_list<CSpecReference<CDataSpecTag, DirTag>> &&pa_loDataRef) {
      getWithFromDir(pa_oEventRef).bind(pa_oEventRef, std::move(pa_loDataRef));
    }
    /**
     * @brief Binds event to data port range.
     * @tparam DirTag defines event/data direction; should be automatically deduced
     * @param pa_oEventRef event from #m_oEI or #m_oEO
     * @param pa_oFirstDataRef first data from #m_oDI or #m_oDO
     * @param pa_oFirstDataRef last data from #m_oDI or #m_oDO
     */
    template<class DirTag>
    void bindRange(CSpecReference<CEventSpecTag, DirTag> pa_oEventRef, CSpecReference<CDataSpecTag, DirTag> pa_oFirstDataRef, CSpecReference<CDataSpecTag, DirTag> pa_oLastDataRef) {
      getWithFromDir(pa_oEventRef).bindRange(pa_oEventRef, pa_oFirstDataRef, pa_oLastDataRef);
    }
    /**
     * @brief Binds event to data port range.
     * @tparam DirTag defines event/data direction; should be automatically deduced
     * @param pa_oEventRef event from #m_oEI or #m_oEO
     * @param pa_oDataRefRange data range from #m_oDI or #m_oDO
     */
    template<class DirTag>
    void bindRange(CSpecReference<CEventSpecTag, DirTag> pa_oEventRef, CSpecReferenceRange<CDataSpecTag, DirTag> pa_oDataRefRange) {
      getWithFromDir(pa_oEventRef).bindRange(pa_oEventRef, pa_oDataRefRange);
    }

    /**
     * @brief Builds @ref SFBInterfaceSpec and fills storage with dynamic data.
     *
     * Before calling this function events, data and withs need to be configured.
     *
     * @param pa_oStorage storage containing dynamic data
     * @param pa_oInterfaceSpec @ref SFBInterfaceSpec to fill out
     * @return isGood()
     */
    bool build(CMixedStorage &pa_oStorage, SFBInterfaceSpec &pa_oInterfaceSpec);

    /**
     * @brief Checks builder status
     * @return true if everything's ok
     */
    bool isGood() const;

  private:
    bool m_bIsGood = true;

    constexpr CWithSpecBuilder<CInputSpecTag>& getWithFromDir(CSpecReference<CEventSpecTag, CInputSpecTag>) {
      return m_oIWith;
    }
    constexpr CWithSpecBuilder<COutputSpecTag>& getWithFromDir(CSpecReference<CEventSpecTag, COutputSpecTag>) {
      return m_oOWith;
    }
};

}

#endif /* _IF_SPEC_BUILDER_H_ */
